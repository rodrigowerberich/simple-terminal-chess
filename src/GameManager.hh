#pragma once

#include "GameResources.hh"
// #include "CommandQuit.hh"
#include "ParserInterface.hh"
#include "Printer.hh"

namespace Chess{

class GameManager{
public:
    GameManager(Chess::Input::ParserInterface& parser, Chess::Output::Printer& printer);
    void init();
    bool run();
private:
    // Chess::Input::Commands::CommandQuit m_commandQuit;
    Chess::GameResources m_resources;
    void printStartGameMessage();
    
};

}