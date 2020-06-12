#include "GameManager.hh"
#include "Input/Parser.hh"
#include "Output/UserInterface/MessageSelector.hh"

#include <iostream>

namespace Chess{

GameManager::GameManager(Chess::Resources::GameResourcesInterface& resources,
                         Chess::Command::ManagerInterface& commandManager):
m_resources{resources}, m_commandManager{commandManager}{

}

void GameManager::init(){
    printStartGameMessage();
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