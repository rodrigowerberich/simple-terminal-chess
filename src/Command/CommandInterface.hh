#pragma once

#include "Input/ParsedInput.hh"
#include "Resources/GameResourcesInterface.hh"

namespace Chess{

namespace Command{

class CommandInterface{
public:
    virtual void init(Chess::Resources::GameResourcesInterface& gameResources) = 0;
    virtual bool activated(const Chess::Input::ParsedInput& parsedInput) = 0;
    virtual bool execute(Chess::Resources::GameResourcesInterface& gameResources) = 0;
};

}

}