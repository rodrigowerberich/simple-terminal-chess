#include "CommandQuit.hh"

namespace Chess{
namespace Input{
namespace Commands{

void CommandQuit::init(GameResources& gameResources){

}

bool CommandQuit::activated(const std::string& commandLine){
    return (commandLine == "exit") || (commandLine == "quit");
}

bool CommandQuit::execute(GameResources& gameResources){
    return false;
}

}
}
}