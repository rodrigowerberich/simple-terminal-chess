#pragma once

#include "CommandInterface.hh"

namespace Chess{

class GameResources;

namespace Input {

class ParserInterface
{
public:
    virtual CommandInterface& parse(GameResources& gameResources) = 0;
    virtual void addCommand(CommandInterface& command) = 0;
};

}
}