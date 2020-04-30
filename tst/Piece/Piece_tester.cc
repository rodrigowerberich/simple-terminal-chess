#include <string>
#include <vector>
#include <iostream>

#include "Piece.hh"

int main(){
    using namespace Chess;
    auto result = true;

    // result &= (position.toString() == validPositionsStrings[counter]);

    if(result){
        std::cout << "Piece is working as intended!\n";
    }else{
        std::cout << "Piece has failed!\n";
    }
    
    return result;

}