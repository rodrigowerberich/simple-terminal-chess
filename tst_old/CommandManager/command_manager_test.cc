#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "Command/Manager.hh"
#include "Command/Quit.hh"#include "Input/ParsedInput.hh"

class GameResource{    
};

int main(){

    Chess::Command::Manager commandManager;

    Chess::Command::Quit quitCommand;

    commandManager.add(quitCommand);

    ParsedInput exitInput = {"exit"}



    if(result){
        std::cout << "Parser is working as intended!\n";
    }else{
        std::cout << "Parser is failed!\n";
    }
    
    return result;
}