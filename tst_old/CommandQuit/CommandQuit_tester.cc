#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "Command/Quit.hh"#include "Input/ParsedInput.hh"

namespace Chess{
    
class GameResources{    
};

}


int main(){

    Chess::GameResources gr;
    Chess::Input::ParsedInput inputCorrect1 = {"exit"};
    Chess::Input::ParsedInput inputCorrect2 = {"quit"};
    Chess::Input::ParsedInput inputIncorrect1 = {"quitanda"};
    Chess::Input::ParsedInput inputIncorrect2 = {"exitando"};
    Chess::Input::ParsedInput inputIncorrect3 = {""};
    Chess::Input::ParsedInput inputIncorrect4 = {"exit","banana"};

    Chess::Command::Quit quit;

    quit.init(gr);
    auto result1 = quit.activated(inputCorrect1);
    auto result2 = quit.activated(inputCorrect2);
    auto result3 = !quit.activated(inputIncorrect1);
    auto result4 = !quit.activated(inputIncorrect2);
    auto result5 = !quit.activated(inputIncorrect3);
    auto result6 = !quit.activated(inputIncorrect4);
    
    // Quit always returns false
    auto result7 = !quit.execute(gr);

    auto result = result1 && result2 && result3 && result4 && result5 && result6 && result7;

    if(result){
        std::cout << "CommandQuit is working as intended!\n";
    }else{
        std::cout << "CommandQuit is failed!\n";
    }

    return 0;
}