#include <iostream> // Remove

#include "CommandUnrecognized.hh"

namespace Chess{
namespace Input{
namespace Commands{

void CommandUnrecognized::init(GameResources& gameResources){

}

bool CommandUnrecognized::activated(const std::string& commandLine){
    return false;
}

bool CommandUnrecognized::execute(GameResources& gameResources){
    std::cout << "Unrecognized command \"" << m_unrecognizedCommandString << "\"\n";
    return true;
}

void CommandUnrecognized::setUnrecognizedString(const std::string & unrecognizedCommandString){
    m_unrecognizedCommandString = unrecognizedCommandString;
}


}
}
}