#include "Rules/MoveRequester.hh"
#include "Rules/QueenMoveRequester.hh"
#include "Rules/PieceMoverAux.hh"
#include "Board/BoardDefinitions.hh"

#include <iostream>
namespace Chess{
namespace Rules{
namespace QueenMoveRequester{


std::vector<Chess::Board::Position> queenPath(const Chess::Board::Position& initialPosition, const Chess::Board::Position& finalPosition){
    std::vector<Chess::Board::Position> path;
    if(!initialPosition.isValid() || !finalPosition.isValid()){
        return path;
    }

    // Normal queen movement is on the same column, row or on a diagonal
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
    }else if(Chess::Rules::PieceMoverAux::isDiagonal(initialPosition, finalPosition)){
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
MoveProposalAnalysis MoveRequester::verifyMove<Chess::Board::PieceType::Queen>(const BoardType& originalBoard, const BoardType& newBoard, const PieceDescriptionType& pieceDescription, const MoveResultType& moveResult){
    auto originalPosition = originalBoard.getPiecePosition(pieceDescription);
    auto finalPosition = newBoard.getPiecePosition(pieceDescription);
    if(moveResult.status() == Chess::Board::MoveResult::Status::Collision){
        finalPosition = moveResult.info<Chess::Board::MoveResult::Info::Collision>().position;
    }
    // Queen path only returns horizontal or vertical paths.
    auto path = QueenMoveRequester::queenPath(originalPosition, finalPosition);

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