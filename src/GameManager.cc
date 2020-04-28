#include "GameManager.hh"
#include "Parser.hh"

#include <iostream>

namespace Chess{

GameManager::GameManager(Chess::Input::ParserInterface& parser):
m_resources{parser}{

}

void GameManager::init(){
    m_commandQuit.init(m_resources);

    m_resources.parser().addCommand(m_commandQuit);
}

bool GameManager::run(){
    return m_resources.parser().parse(m_resources);
}

}