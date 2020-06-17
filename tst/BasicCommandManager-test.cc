#include "gtest/gtest.h"
#include "Command/Quit.hh"
#include "Resources/GameResources.hh"
#include "Output/UserInterface/VerySimpleMessageManager.hh"
#include "Output/UserInterface/MessageSelector.hh"
#include "BasicGameConfiguration.hh"
#include "Command/BasicManager.hh"
#include "Output/Printer.hh"
#include "Input/Parser.hh"

#include <sstream>
#include <vector>

TEST(BasicCommandManager, addAndRunQuitManager) {   
    std::stringstream inputStream;
    std::stringstream outputStream;


    auto parser = Chess::Input::Parser(inputStream);
    auto printer = Chess::Output::Printer(outputStream);
    auto messageManager = Chess::Output::UserInterface::VerySimpleMessageManager();
    auto configuration = Chess::BasicGameConfiguration();

    auto resources = Chess::Resources::GameResources{
        parser,
        printer,
        messageManager,
        configuration        
    };

    auto manager = Chess::Command::BasicManager();
    auto quit = Chess::Command::Quit();

    manager.addCommand(quit);
    
    auto input = Chess::Input::ParsedInput{"exit"};
    ASSERT_EQ(manager.processInput(input, resources), Chess::Command::ManagerInterface::ProcessResult::Failed);
}

TEST(BasicCommandManager, notFindAnyCommand) {   
    std::stringstream inputStream;
    std::stringstream outputStream;


    auto parser = Chess::Input::Parser(inputStream);
    auto printer = Chess::Output::Printer(outputStream);
    auto messageManager = Chess::Output::UserInterface::VerySimpleMessageManager();
    auto configuration = Chess::BasicGameConfiguration();

    auto resources = Chess::Resources::GameResources{
        parser,
        printer,
        messageManager,
        configuration        
    };

    auto manager = Chess::Command::BasicManager();
    
    auto input = Chess::Input::ParsedInput{"nothing"};
    ASSERT_EQ(manager.processInput(input, resources), Chess::Command::ManagerInterface::ProcessResult::NoCommandFound);
}

TEST(BasicCommandManager, addMultipleCommandsThatRespondToTheSameInput) {   
    std::stringstream inputStream;
    std::stringstream outputStream;


    auto parser = Chess::Input::Parser(inputStream);
    auto printer = Chess::Output::Printer(outputStream);
    auto messageManager = Chess::Output::UserInterface::VerySimpleMessageManager();
    auto configuration = Chess::BasicGameConfiguration();

    auto resources = Chess::Resources::GameResources{
        parser,
        printer,
        messageManager,
        configuration        
    };

    auto manager = Chess::Command::BasicManager();
    auto quit1 = Chess::Command::Quit();
    auto quit2 = Chess::Command::Quit();

    manager.addCommand(quit1);
    manager.addCommand(quit2);
    
    auto input = Chess::Input::ParsedInput{"exit"};
    ASSERT_EQ(manager.processInput(input, resources), Chess::Command::ManagerInterface::ProcessResult::MultipleCommandsActivated);
}