#pragma once

#include "GameResources.hh"

namespace Chess{

class GameManager{
public:
    GameManager(Chess::Input::ParserInterface& parser, 
                Chess::Output::Printer& printer,
                Chess::Output::UserInterface::MessageManagerInterface& messageManager);
    void init();
    bool run();
private:
    Chess::GameResources m_resources;
    void printStartGameMessage();
    
};

}