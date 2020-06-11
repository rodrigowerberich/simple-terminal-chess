#include "GameManager.hh"
#include "Input/Parser.hh"
#include "Output/UserInterface/MessageSelector.hh"

#include <iostream>

namespace Chess{

GameManager::GameManager(Chess::Input::ParserInterface& parser, 
                         Chess::Output::Printer& printer, 
                         Chess::Output::UserInterface::MessageManagerInterface& messageManager,
                         Chess::GameConfigurationInterface& configuration):
m_resources{parser, printer, messageManager, configuration}{

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
    using namespace Output::UserInterface;
    auto& printer = m_resources.printer();
    auto& messageManager = m_resources.messageManager();

    printer.print(messageManager[MessageSelector::GAME_START_WELCOME_MESSAGE]);
    printer.println();
}


}