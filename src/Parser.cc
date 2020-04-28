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
    m_commands.emplace_back(command);
}

bool Parser::parse(){
    bool execution_ok = true;

    std::string lineRead;
    std::getline(m_inputStream, lineRead);
    std::cout << '"' << lineRead << '"' << std::endl;
    for(auto& command:m_commands){
        if(command.get().activated(lineRead)){
            execution_ok = command.get().execute();
        }
    }
    return execution_ok;
}

}  
}
