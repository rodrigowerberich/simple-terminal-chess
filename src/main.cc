#include <iostream>

#include "GameManager.hh"
#include "Output/Printer.hh"
#include "Input/Parser.hh"
#include "Output/UserInterface/VerySimpleMessageManager.hh"
#include "BasicGameConfiguration.hh"

int main(){
    auto parser = Chess::Input::Parser(std::cin);
    auto printer = Chess::Output::Printer(std::cout);
    auto messageManager = Chess::Output::UserInterface::VerySimpleMessageManager();
    auto configuration = Chess::BasicGameConfiguration();

    auto gameManager = Chess::GameManager{
        parser,
        printer,
        messageManager,
        configuration
    };

    gameManager.init();

    // while(gameManager.run());
    
    return 0;
}