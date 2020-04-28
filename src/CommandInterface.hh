#pragma once

#include <string>

namespace Chess{

class GameResources;

namespace Input {

class CommandInterface{
public:
    virtual void init(GameResources& gameResources) = 0;
    virtual bool activated(const std::string& commandLine) = 0;
    virtual bool execute(GameResources& gameResources) = 0;
};

}
}