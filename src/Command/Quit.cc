#include "Command/Quit.hh"
namespace Chess{
namespace Command{

void Quit::init(GameResources& gameResources){

}

bool Quit::activated(const Chess::Input::ParsedInput& parsedInput){
    return (parsedInput.size() == 1) && ((parsedInput[0] == "exit") || (parsedInput[0] == "quit"));
}

bool Quit::execute(GameResources& gameResources){
    return false;
}

}
}