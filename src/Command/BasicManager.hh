#pragma once

#include "Command/ManagerInterface.hh"

namespace Chess{
namespace Command{

class BasicManager: public ManagerInterface{
private:
    std::vector<Command::CommandInterface*> m_commands;
public:
    void addCommand(CommandInterface& commandToAdd) override;
    void processInput(const Input::ParsedInput& parsedInput, Resources::GameResourcesInterface& gameResources) override;
};

}
}