#include <string>
#include <iostream>
#include <functional>
#include <sstream>

#include "Input/Parser.hh"

namespace Chess{
namespace Input{
    
Parser::Parser(std::istream& inputStream):
m_inputStream{inputStream}{
    
}

Parser::~Parser(){
    
}

ParsedInput Parser::parse() const{
    // Making Sure the parsed input is empty
    ParsedInput parsedInput = {};
    // Read until user types a space
    std::string lineRead;
    std::getline(m_inputStream, lineRead);
    // Using stringstream to be able to read the line 
    // the user typed as a stream
    std::stringstream lineReadStream(lineRead);
    // Separating the line by spaces and saving each word 
    // in a vector 
    std::string word;
    while (std::getline(lineReadStream, word, ' ')) {
        parsedInput.push_back(word);

    }
    return parsedInput;
}

}  
}
