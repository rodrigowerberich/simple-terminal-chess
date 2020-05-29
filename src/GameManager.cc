#include "GameManager.hh"
#include "Input/Parser.hh"

#include <iostream>

namespace Chess{

GameManager::GameManager(Chess::Input::ParserInterface& parser, Chess::Output::Printer& printer):
m_resources{parser, printer}{

}

void GameManager::init(){
    printStartGameMessage();
    // m_commandQuit.init(m_resources);

    // m_resources.parser().addCommand(m_commandQuit);
}

bool GameManager::run(){
    auto parsedInput = m_resources.parser().parse();
    // return command.execute(m_resources);
    return false;
}

void GameManager::printStartGameMessage(){
    auto& printer = m_resources.printer();
    printer.print("Welcome to simple chess");
}


}