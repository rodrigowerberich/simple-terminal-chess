#include "Command/BasicManager.hh"

namespace Chess{
namespace Command{

void BasicManager::addCommand(CommandInterface& commandToAdd){
    m_commands.push_back(&commandToAdd);
}

void BasicManager::processInput(const Input::ParsedInput& parsedInput, Resources::GameResourcesInterface& gameResources){
    
}

}
}