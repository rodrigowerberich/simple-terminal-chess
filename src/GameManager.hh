#pragma once

#include "GameResources.hh"
// #include "Command/Quit.hh"#include "Input/ParserInterface.hh"
#include "Output/Printer.hh"

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