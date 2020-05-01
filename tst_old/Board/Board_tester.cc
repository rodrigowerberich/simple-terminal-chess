#include <string>
#include <sstream>
#include <iostream>
#include <array>
#include <vector>

#include "Board.hh"

int main(){
    auto result = true;
    
    Chess::Board::Board board;
    
    Chess::Board::PieceDescription pieceDescription = {
        Chess::Board::PieceType::Pawn,
        Chess::Board::SideSelector::Black,
        Chess::Board::PieceSelector::Pawn::A
    };
    Chess::Board::Position newPosition = 
    {
        Chess::Board::Column::A,
        4
    };
    
    Chess::Board::MoveResult moveResult = board.move(pieceDescription, newPosition);
    
    Chess::Board::Position currentPosition = board.getPosition(pieceDescription);
    return result;
    
    board.undo();

}