#include "CommandQuit.hh"

namespace Chess{
namespace Input{
namespace Commands{

bool CommandQuit::activated(const std::string& commandLine){
    return (commandLine == "exit") || (commandLine == "quit");
}

bool CommandQuit::execute(){
    return false;
}

}
}
}