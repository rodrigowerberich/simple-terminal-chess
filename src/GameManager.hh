#pragma once

#include "Resources/GameResourcesInterface.hh"
#include "Command/ManagerInterface.hh"
#include "Input/ParsedInput.hh"

namespace Chess{

class GameManager{
public:
    GameManager(Chess::Resources::GameResourcesInterface& resources,
                Chess::Command::ManagerInterface& commandManager);
    void init();
    bool run();
private:
    Chess::Resources::GameResourcesInterface& m_resources;
    Chess::Command::ManagerInterface& m_commandManager;
    void printStartGameMessage();
    bool handleUnrecognizedCommand(Chess::Input::ParsedInput& parsedInput);
};

}