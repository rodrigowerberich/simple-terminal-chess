#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "CommandManager.hh"
#include "CommandQuit.hh"
#include "Input/ParsedInput.hh"

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