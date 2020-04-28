#include <iostream>

#include "Parser.hh"
#include "CommandQuit.hh"

int main(){
    Chess::Input::Commands::CommandQuit commandQuit;

    Chess::Input::Parser gameParser(std::cin);
    gameParser.addCommand(commandQuit);
    while( gameParser.parse());
    return 0;
}