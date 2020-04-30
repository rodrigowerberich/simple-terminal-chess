#include <string>
#include <vector>
#include <iostream>

#include "Piece.hh"

int main(){
    using namespace Chess;
    auto result = true;

    Chess::Board::Piece piece = {Chess::Board::PieceType::Bishop, {Chess::Board::Column::B, 3}};

    std::cout << piece << std::endl;
    // result &= (position.toString() == validPositionsStrings[counter]);

    if(result){
        std::cout << "Piece is working as intended!\n";
    }else{
        std::cout << "Piece has failed!\n";
    }
    
    return result;

}