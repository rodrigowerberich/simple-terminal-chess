#include "Rules/MoveRequester.hh"
#include "Rules/KingMoveRequester.hh"
#include "Rules/PieceMoverAux.hh"
#include "Board/BoardDefinitions.hh"

#include <iostream>
namespace Chess{
namespace Rules{
namespace KingMoveRequester{


std::vector<Chess::Board::Position> kingPath(const Chess::Board::Position& initialPosition, const Chess::Board::Position& finalPosition){
    using Chess::Rules::PieceMoverAux::isDiagonal;
    using Chess::Rules::PieceMoverAux::manhattanDistance;
    std::vector<Chess::Board::Position> path;
    if(!initialPosition.isValid() || !finalPosition.isValid()){
        return path;
    }

    // Normal king movement is on the same column, row or on a diagonal
    if(isDiagonal(initialPosition, finalPosition) 
       && (manhattanDistance(initialPosition, finalPosition) == 2) ){
        path = {initialPosition, finalPosition};
    }else if(manhattanDistance(initialPosition, finalPosition) == 1){
        path = {initialPosition, finalPosition};
    }
    return path;
}

}

template <>
MoveProposalAnalysis MoveRequester::verifyMove<Chess::Board::PieceType::King>(const BoardType& originalBoard, const BoardType& newBoard, const PieceDescriptionType& pieceDescription, const MoveResultType& moveResult){
    auto originalPosition = originalBoard.getPiecePosition(pieceDescription);
    auto finalPosition = newBoard.getPiecePosition(pieceDescription);
    if(moveResult.status() == Chess::Board::MoveResult::Status::Collision){
        finalPosition = moveResult.info<Chess::Board::MoveResult::Info::Collision>().position;
    }
    // King path only returns horizontal or vertical paths.
    auto path = KingMoveRequester::kingPath(originalPosition, finalPosition);

    auto pathSize = static_cast<int>(path.size());
    if(pathSize > 1){
        for(int pathIndex = 1; pathIndex < pathSize-1; pathIndex++){
            auto possibilityOfCollisionPosition = path[pathIndex];
            auto possiblePieceDescription = originalBoard.getPieceAtPosition(possibilityOfCollisionPosition);
            if(possiblePieceDescription.isValid()){
                return {originalBoard, Rules::MovementInterrupted{originalPosition, possibilityOfCollisionPosition, finalPosition, pieceDescription, possiblePieceDescription}};
            }
        }
        return {newBoard, moveResult};
    }

    return {originalBoard, Rules::InvalidPieceMovement{originalPosition, finalPosition, pieceDescription}};
}

}    
}