#include "gtest/gtest.h"
#include "Command/Quit.hh"
#include "Resources/Fakes/OnlyLanguageGameResources.hh"
#include "Output/UserInterface/VerySimpleMessageManager.hh"
#include "BasicGameConfiguration.hh"

#include <vector>

TEST(CommandQuit, correctInputs) {    
    auto correctInputs = std::vector<Chess::Input::ParsedInput>{
        {"exit"},
        {"quit"}
    };

    auto quit = Chess::Command::Quit{};
    for(const auto& correctInput: correctInputs){
        ASSERT_TRUE(quit.activated(correctInput));
    }
}

TEST(CommandQuit, incorrectInputs) {


   auto incorrectInputs = std::vector<Chess::Input::ParsedInput>{
        {"quitanda"},
        {"exitando"},
        {""},
        {"exit","banana"}
    };

    auto quit = Chess::Command::Quit{};
    for(const auto& incorrectInput: incorrectInputs){
        ASSERT_FALSE(quit.activated(incorrectInput));
    }
}

TEST(CommandQuit, initEN){
    auto basicMessageManager = Chess::Output::UserInterface::VerySimpleMessageManager();
    auto gameConfiguration = Chess::BasicGameConfiguration();

    auto gameResources = Chess::Resources::Fakes::OnlyLanguageGameResources{
        basicMessageManager,
        gameConfiguration
    };
    auto quit = Chess::Command::Quit{};
    quit.init(gameResources);

    auto correctInputs = std::vector<Chess::Input::ParsedInput>{
        {"exit"},
        {"quit"}
    };

    for(const auto& correctInput: correctInputs){
        ASSERT_TRUE(quit.activated(correctInput));
    }

}