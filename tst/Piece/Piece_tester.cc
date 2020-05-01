#include <string>
#include <vector>
#include <iostream>

#include "Piece.hh"
    
    // Chess::Board::PieceType type() const;
    // const Chess::Board::Position& currentPosition() const;
    // void setPosition(const Chess::Board::Position& position);


int main(){
    using namespace Chess;
    auto result = true;

    Chess::Board::Piece piece = {Chess::Board::PieceType::Bishop, {Chess::Board::Column::B, 3}};
    std::cout << piece << std::endl;
    result &= 
    std::cout << piece.type() << std::endl;
    std::cout << piece.currentPosition() << std::endl;
    piece.setPosition({Chess::Board::Column::D, 1});
    std::cout << piece.currentPosition() << std::endl;

    // result &= (position.toString() == validPositionsStrings[counter]);

    if(result){
        std::cout << "Piece is working as intended!\n";
    }else{
        std::cout << "Piece has failed!\n";
    }
    
    return result;

}