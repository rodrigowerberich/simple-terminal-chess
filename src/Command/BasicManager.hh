#pragma once

#include "Command/ManagerInterface.hh"

namespace Chess{
namespace Command{

class BasicManager: public ManagerInterface{
private:
    std::vector<Command::CommandInterface*> m_commands;
public:
    void addCommand(CommandInterface& commandToAdd) override;
    ManagerInterface::ProcessResult processInput(const Input::ParsedInput& parsedInput, Resources::GameResourcesInterface& gameResources) override;
    HelpTexts helpTexts() const;

};

}
}