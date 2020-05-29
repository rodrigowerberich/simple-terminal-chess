#pragma once

#include "Input/ParsedInput.hh"

namespace Chess{

class GameResources;

namespace Command{

class CommandInterface{
public:
    virtual void init(GameResources& gameResources) = 0;
    virtual bool activated(const Chess::Input::ParsedInput& parsedInput) = 0;
    virtual bool execute(GameResources& gameResources) = 0;
};

}

}