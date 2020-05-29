#include "Rules/MoveRequester.hh"
#include "KnightMoveRequester.hh"
#include "Rules/PieceMoverAux.hh"
#include "Board/Definitions.hh"

#include <iostream>
namespace Chess{
namespace Rules{
namespace KnightMoveRequester{


// std::vector<Chess::Board::Position> knightPath(const Chess::Board::Position& initialPosition, const Chess::Board::Position& finalPosition){
    // std::vector<Chess::Board::Position> path;
    // if(!initialPosition.isValid() || !finalPosition.isValid()){
    //     return path;
    // }

    // // Normal knight movement is only in the same column
    // if(initialPosition.column() == finalPosition.column()){
    //     auto initialRow = initialPosition.row();
    //     auto finalRow = finalPosition.row();
    //     auto smallToBig = initialRow < finalRow;
    //     auto distance = std::abs(finalRow - initialRow);
    //     for(auto index = 0; index <= distance; index++ ){
    //         auto row = initialRow + index*(smallToBig?1:-1);
    //         path.push_back({initialPosition.column(), row});
    //     }
    // }else if(initialPosition.row() == finalPosition.row()){
    //     auto initialPositionNumber = PieceMoverAux::InternalPosition(initialPosition);
    //     auto finalPositionNumber = PieceMoverAux::InternalPosition(finalPosition);
    //     auto initialColumn = initialPositionNumber.column();
    //     auto finalColumn = finalPositionNumber.column();
    //     auto smallToBig = initialColumn < finalColumn;
    //     auto distance = std::abs(finalColumn - initialColumn);
    //     for(auto index = 0; index <= distance; index++ ){
    //         auto column = initialColumn + index*(smallToBig?1:-1);
    //         path.push_back({PieceMoverAux::columnFromNumber(column), initialPosition.row()});
    //     }
    // }
    // return path;
// }

}

template <>
MoveProposalAnalysis MoveRequester::verifyMove<Chess::Board::PieceType::Knight>(const BoardType& originalBoard, const BoardType& newBoard, const PieceDescriptionType& pieceDescription, const MoveResultType& moveResult){
    auto originalPosition = originalBoard.getPiecePosition(pieceDescription);
    auto finalPosition = newBoard.getPiecePosition(pieceDescription);
    if(moveResult.status() == Chess::Board::MoveResult::Status::Collision){
        finalPosition = moveResult.info<Chess::Board::MoveResult::Info::Collision>().position;
    }
    
    if(!originalPosition.isValid() || !finalPosition.isValid()){
        return {originalBoard, Rules::InvalidPieceMovement{originalPosition, finalPosition, pieceDescription}};
    }
    // Knight does not have a path, it only jumps from a place to the other, it skips over the other pieces
    // The knight can move in a L shape
    // |   |   |   |   |   |   |   |
    // |   |   | V |   | V |   |   |
    // |   | V |   |   |   | V |   |
    // |   |   |   | k |   |   |   |
    // |   | V |   |   |   | V |   |
    // |   |   | V |   | V |   |   |
    // |   |   |   |   |   |   |   |
    // k - is the knight current position
    // V is the valid places that he can land
    // That means it can land in a place with a manhattan distance of 3 that does not has the same row or column as the knight
    if((PieceMoverAux::manhattanDistance(originalPosition, finalPosition) == 3) && 
       (originalPosition.column() != finalPosition.column()) && 
       (originalPosition.row() != finalPosition.row())){
        return {newBoard, moveResult};
    }
    return {originalBoard, Rules::InvalidPieceMovement{originalPosition, finalPosition, pieceDescription}};
}

}    
}