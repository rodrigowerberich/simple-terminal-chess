#include <iostream>

#include "GameManager.hh"
#include "Output/Printer.hh"
#include "Input/Parser.hh"
#include "Output/UserInterface/VerySimpleMessageManager.hh"
#include "BasicGameConfiguration.hh"
#include "Command/BasicManager.hh"

#include "Resources/GameResources.hh"

#include "Command/Quit.hh"
#include "Command/Help.hh"

int main(){
    auto parser = Chess::Input::Parser(std::cin);
    auto printer = Chess::Output::Printer(std::cout);
    auto messageManager = Chess::Output::UserInterface::VerySimpleMessageManager();
    auto configuration = Chess::BasicGameConfiguration();
    auto commandManager = Chess::Command::BasicManager();

    auto resources = Chess::Resources::GameResources{
        parser,
        printer,
        messageManager,
        configuration        
    };

    auto gameManager = Chess::GameManager{
        resources,
        commandManager
    };

    auto quitCommand = Chess::Command::Quit();

    auto helpCommand = Chess::Command::Help(commandManager);

    commandManager.addCommand(quitCommand);
    commandManager.addCommand(helpCommand);

    gameManager.init();

    while(gameManager.run());
    
    return 0;
}