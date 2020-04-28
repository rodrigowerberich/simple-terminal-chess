#include <string>
#include <iostream>
#include <functional>

#include "Parser.hh"

namespace Chess{
namespace Input{
    
Parser::Parser(std::istream& inputStream):
m_inputStream{inputStream}{
    
}

Parser::~Parser(){
    
}

void Parser::addCommand(CommandInterface& command){
    m_commands.push_back(command);
}

CommandInterface& Parser::parse(GameResources& gameResources){
    std::string lineRead;
    std::getline(m_inputStream, lineRead);


    for(auto& command:m_commands){
        if(command.get().activated(lineRead)){
            return command.get();
        }
    }

    m_commandUnrecognized.setUnrecognizedString(lineRead);
    return m_commandUnrecognized;
}

}  
}
