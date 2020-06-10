#include <iostream>

#include "GameManager.hh"
#include "Output/Printer.hh"
#include "Input/Parser.hh"
#include "Output/UserInterface/VerySimpleMessageManager.hh"

int main(){
    auto parser = Chess::Input::Parser(std::cin);
    auto printer = Chess::Output::Printer(std::cout);
    auto messageManager = Chess::Output::UserInterface::VerySimpleMessageManager();


    auto gameManager = Chess::GameManager{
        parser,
        printer,
        messageManager
    };

    gameManager.init();

    // while(gameManager.run());
    
    return 0;
}