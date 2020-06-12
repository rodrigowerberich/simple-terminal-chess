#pragma once

#include "Command/CommandInterface.hh"
#include "Input/ParsedInput.hh"
#include "Resources/GameResourcesInterface.hh"

namespace Chess{
namespace Command{

class ManagerInterface{
public:
    virtual void addCommand(CommandInterface& commandToAdd) = 0;
    virtual void processInput(const Input::ParsedInput& parsedInput, Resources::GameResourcesInterface& gameResources) = 0;
};

}
}