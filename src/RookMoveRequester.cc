#include "MoveRequester.hh"
#include "RookMoveRequester.hh"
#include "PieceMoverAux.hh"
#include "BoardDefinitions.hh"

#include <iostream>
namespace Chess{
namespace Rules{
namespace RookMoveRequester{


std::vector<Chess::Board::Position> rookPath(const Chess::Board::Position& initialPosition, const Chess::Board::Position& finalPosition){
    std::vector<Chess::Board::Position> path;
    if(!initialPosition.isValid() || !finalPosition.isValid()){
        return path;
    }

    // Normal rook movement is only in the same column
    if(initialPosition.column() == finalPosition.column()){
        auto initialRow = initialPosition.row();
        auto finalRow = finalPosition.row();
        auto smallToBig = initialRow < finalRow;
        auto distance = std::abs(finalRow - initialRow);
        for(auto index = 0; index <= distance; index++ ){
            auto row = initialRow + index*(smallToBig?1:-1);
            path.push_back({initialPosition.column(), row});
        }
    }else if(initialPosition.row() == finalPosition.row()){
        auto initialPositionNumber = PieceMoverAux::InternalPosition(initialPosition);
        auto finalPositionNumber = PieceMoverAux::InternalPosition(finalPosition);
        auto initialColumn = initialPositionNumber.column();
        auto finalColumn = finalPositionNumber.column();
        auto smallToBig = initialColumn < finalColumn;
        auto distance = std::abs(finalColumn - initialColumn);
        for(auto index = 0; index <= distance; index++ ){
            auto column = initialColumn + index*(smallToBig?1:-1);
            path.push_back({PieceMoverAux::columnFromNumber(column), initialPosition.row()});
        }
    }
    return path;
}

}

template <>
MoveProposalAnalysis MoveRequester::verifyMove<Chess::Board::PieceType::Rook>(const BoardType& originalBoard, const BoardType& newBoard, const PieceDescriptionType& pieceDescription, const MoveResultType& moveResult){
    return {originalBoard};
}

}    
}