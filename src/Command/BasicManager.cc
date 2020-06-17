#include "Command/BasicManager.hh"

namespace Chess{
namespace Command{

void BasicManager::addCommand(CommandInterface& commandToAdd){
    m_commands.push_back(&commandToAdd);
}

ManagerInterface::ProcessResult BasicManager::processInput(const Input::ParsedInput& parsedInput, Resources::GameResourcesInterface& gameResources){
    std::vector<Command::CommandInterface*> activatedCommand;
    for(const auto& p_command: m_commands){
        if(p_command->activated(parsedInput)){
            activatedCommand.push_back(p_command);
        }
    }
    if(activatedCommand.size() > 1){
        return ManagerInterface::ProcessResult::MultipleCommandsActivated;
    }else if(activatedCommand.size() == 0){
        return ManagerInterface::ProcessResult::NoCommandFound;
    }else{
        return (activatedCommand[0]->execute(gameResources))?
                ManagerInterface::ProcessResult::OK:
                ManagerInterface::ProcessResult::Failed;
    }
}

HelpTexts BasicManager::helpTexts() const{
    HelpTexts helpTexts = {};
    for(const auto& p_command: m_commands){
        auto helpText = p_command->helpText();
        if(!helpText.empty()){
            helpTexts.push_back(helpText);
        }
    }
    return helpTexts;
}


}
}