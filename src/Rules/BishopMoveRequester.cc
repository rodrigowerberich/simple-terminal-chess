#include "Rules/MoveRequester.hh"
#include "Rules/BishopMoveRequester.hh"
#include "Rules/PieceMoverAux.hh"
#include "Board/BoardDefinitions.hh"

#include <iostream>
namespace Chess{
namespace Rules{
namespace BishopMoveRequester{


std::vector<Chess::Board::Position> bishopPath(const Chess::Board::Position& initialPosition, const Chess::Board::Position& finalPosition){
    std::vector<Chess::Board::Position> path;
    if(!initialPosition.isValid() || !finalPosition.isValid()){
        return path;
    }

    // Normal bishop movement is only diagonal 
    if(Chess::Rules::PieceMoverAux::isDiagonal(initialPosition, finalPosition)){
        auto initialPositionNumber = PieceMoverAux::InternalPosition(initialPosition);
        auto finalPositionNumber = PieceMoverAux::InternalPosition(finalPosition);
        
        auto initialColumn = initialPositionNumber.column();
        auto finalColumn = finalPositionNumber.column();

        auto initialRow = initialPosition.row();
        auto finalRow = finalPosition.row();

        auto smallToBigColumn = initialColumn < finalColumn;
        auto smallToBigRow = initialRow < finalRow;
        auto distance = std::abs(finalRow - initialRow);
        for(auto index = 0; index <= distance; index++ ){
            auto column = initialColumn + index*(smallToBigColumn?1:-1);
            auto row = initialRow + index*(smallToBigRow?1:-1);
            path.push_back({Chess::Rules::PieceMoverAux::columnFromNumber(column), row});
        }
    }
    return path;
}

}

template <>
MoveProposalAnalysis MoveRequester::verifyMove<Chess::Board::PieceType::Bishop>(const BoardType& originalBoard, const BoardType& newBoard, const PieceDescriptionType& pieceDescription, const MoveResultType& moveResult){
    auto originalPosition = originalBoard.getPiecePosition(pieceDescription);
    auto finalPosition = newBoard.getPiecePosition(pieceDescription);
    if(moveResult.status() == Chess::Board::MoveResult::Status::Collision){
        finalPosition = moveResult.info<Chess::Board::MoveResult::Info::Collision>().position;
    }
    // Bishop path only returns diagonal paths.
    auto path = BishopMoveRequester::bishopPath(originalPosition, finalPosition);

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