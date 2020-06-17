#pragma once

#include "Command/CommandInterface.hh"
#include "Input/ParsedInput.hh"
#include "Resources/GameResourcesInterface.hh"

namespace Chess{
namespace Command{

using HelpTexts = std::vector<std::string>;

class ManagerInterface{
public:
enum class ProcessResult{
    NoCommandFound,
    MultipleCommandsActivated,
    Failed,
    OK
};
    virtual void addCommand(CommandInterface& commandToAdd) = 0;
    virtual ProcessResult processInput(const Input::ParsedInput& parsedInput, Resources::GameResourcesInterface& gameResources) = 0;
    virtual HelpTexts helpTexts() const = 0;
};

}
}