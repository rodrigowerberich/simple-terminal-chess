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
    auto result = m_commandManager.processInput(parsedInput, m_resources);

    using ProcessResult = Chess::Command::ManagerInterface::ProcessResult;
    switch (result){
    case ProcessResult::NoCommandFound:{
        return handleUnrecognizedCommand(parsedInput);
    }
    case ProcessResult::MultipleCommandsActivated:{
        return false;
    }
    case ProcessResult::Failed :{
        return false;
    }
    case ProcessResult::OK:{
        return true;
    }
    default:
        return false;
    }
}

void GameManager::printStartGameMessage(){
    using namespace Output::UserInterface;
    
    auto& printer = m_resources.printer();
    auto& messageManager = m_resources.messageManager();

    printer.print(messageManager[MessageSelector::GAME_START_WELCOME_MESSAGE]);
    printer.println();
}

bool GameManager::handleUnrecognizedCommand(Chess::Input::ParsedInput& parsedInput){
    using namespace Output::UserInterface;
    m_resources.printer().print(m_resources.messageManager()[MessageSelector::BEFORE_UNRECOGNIZED_INPUT_MESSAGE]);
    m_resources.printer().print(" \"");
    m_resources.printer().print(parsedInput);
    m_resources.printer().print("\" ");
    m_resources.printer().println(m_resources.messageManager()[MessageSelector::AFTER_UNRECOGNIZED_INPUT_MESSAGE]);
    return true;
}


}