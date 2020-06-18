#include "gtest/gtest.h"
#include "Command/Quit.hh"
#include "Command/Help.hh"
#include "Command/BasicManager.hh"
#include "Resources/Fakes/OnlyLanguageGameResources.hh"
#include "Resources/Fakes/NothingGameResources.hh"
#include "Output/UserInterface/VerySimpleMessageManager.hh"
#include "Output/UserInterface/MessageSelector.hh"
#include "BasicGameConfiguration.hh"

#include <vector>

TEST(CommandHelp, correctInputs) {    
    auto manager = Chess::Command::BasicManager();

    auto correctInputs = std::vector<Chess::Input::ParsedInput>{
        {"help"},
        {"HELP"},
        {"Help"},
        {"HelP"},
    };

    auto help = Chess::Command::Help{manager};
    for(const auto& correctInput: correctInputs){
        ASSERT_TRUE(help.activated(correctInput));
    }
}

TEST(CommandHelp, incorrectInputs) {    
    auto manager = Chess::Command::BasicManager();

    auto incorrectInputs = std::vector<Chess::Input::ParsedInput>{
        {"xelp"},
        {"ELP"},
        {""},
        {"Banana"},
    };

    auto help = Chess::Command::Help{manager};
    for(const auto& incorrectInput: incorrectInputs){
        ASSERT_FALSE(help.activated(incorrectInput));
    }
}

TEST(CommandHelp, empty) {    
    auto commandManager = Chess::Command::BasicManager();
    auto basicMessageManager = Chess::Output::UserInterface::VerySimpleMessageManager();
    auto gameConfiguration = Chess::BasicGameConfiguration();

    auto gameResources = Chess::Resources::Fakes::OnlyLanguageGameResources{
        basicMessageManager,
        gameConfiguration
    };


    auto help = Chess::Command::Help{commandManager};
    commandManager.addCommand(help);

    help.init(gameResources);
    auto helpTexts = commandManager.helpTexts();
    ASSERT_TRUE(helpTexts.empty());
}

TEST(CommandHelp, quitHelpText) {    
    auto commandManager = Chess::Command::BasicManager();
    auto basicMessageManager = Chess::Output::UserInterface::VerySimpleMessageManager();
    auto gameConfiguration = Chess::BasicGameConfiguration();

    auto gameResources = Chess::Resources::Fakes::OnlyLanguageGameResources{
        basicMessageManager,
        gameConfiguration
    };


    auto help = Chess::Command::Help{commandManager};
    auto quit = Chess::Command::Quit{};
    
    commandManager.addCommand(help);
    commandManager.addCommand(quit);

    help.init(gameResources);
    quit.init(gameResources);
    auto helpTexts = commandManager.helpTexts();
    ASSERT_TRUE(!helpTexts.empty());
    ASSERT_EQ(helpTexts.size(),1);
    ASSERT_EQ(helpTexts[0], "To close the program type any of the following: \"exit\", \"quit\".");
}

