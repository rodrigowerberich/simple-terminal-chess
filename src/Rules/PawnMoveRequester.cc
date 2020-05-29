#include "Rules/MoveRequester.hh"
#include "Rules/PawnMoveRequester.hh"
#include "Rules/PieceMoverAux.hh"
#include "Board/Definitions.hh"

#include <iostream>
namespace Chess{
namespace Rules{
namespace PawnMoveRequester{

std::vector<Chess::Board::Position> pawnPath(const Chess::Board::Position& initialPosition, const Chess::Board::Position& finalPosition){
    std::vector<Chess::Board::Position> path;
    if(!initialPosition.isValid() || !finalPosition.isValid()){
        return path;
    }

    // Normal pawn movement is only in the same column
    if(initialPosition.column() == finalPosition.column()){
        auto initialRow = initialPosition.row();
        auto finalRow = finalPosition.row();
        auto smallToBig = initialRow < finalRow;
        auto distance = std::abs(finalRow - initialRow);
        for(auto index = 0; index <= distance; index++ ){
            auto row = initialRow + index*(smallToBig?1:-1);
            path.push_back({initialPosition.column(), row});
        }
    }else if(PieceMoverAux::isDiagonal(initialPosition, finalPosition) && (PieceMoverAux::manhattanDistance(initialPosition, finalPosition) == 2)){
        path = {initialPosition, finalPosition};
    }
    return path;
}

}

template <>
MoveProposalAnalysis MoveRequester::verifyMove<Chess::Board::PieceType::Pawn>(const BoardType& originalBoard, const BoardType& newBoard, const PieceDescriptionType& pieceDescription, const MoveResultType& moveResult){
    auto originalPosition = originalBoard.getPiecePosition(pieceDescription);
    auto finalPosition = newBoard.getPiecePosition(pieceDescription);
    if(moveResult.status() == Chess::Board::MoveResult::Status::Collision){
        finalPosition = moveResult.info<Chess::Board::MoveResult::Info::Collision>().position;
    }
    auto path = PawnMoveRequester::pawnPath(originalPosition, finalPosition);
    auto pathSize = path.size();
    if(pathSize > 3){
        return {originalBoard, Rules::InvalidPieceMovement{originalPosition, finalPosition, pieceDescription}};
    }else if(pathSize == 3){
        // Check if position in the middle is occupied, and if it is return an error
        // Check if piece can move more than one space
        if(moveResult.status() == Chess::Board::MoveResult::Status::Collision){
            return {originalBoard, Rules::InvalidPieceMovement{originalPosition, finalPosition, pieceDescription}}; // TODO Changes this to a new type or add more info
        }
        if((pieceDescription.sideSelector() == Chess::Board::SideSelector::Black && originalPosition.row() != Chess::Board::Definitions::BLACK_FRONT_ROW) ||
           (pieceDescription.sideSelector() == Chess::Board::SideSelector::White && originalPosition.row() != Chess::Board::Definitions::WHITE_FRONT_ROW)){
            return {originalBoard, Rules::InvalidPieceMovement{originalPosition, finalPosition, pieceDescription}}; // TODO Changes this to a new type or add more info
        }
        auto possibilityOfCollisionPosition = path[1];
        auto pieceAtMiddleDescription = originalBoard.getPieceAtPosition(possibilityOfCollisionPosition);
        if(pieceAtMiddleDescription.isValid()){
            return {originalBoard, Rules::MovementInterrupted{originalPosition, possibilityOfCollisionPosition, finalPosition, pieceDescription, pieceAtMiddleDescription}}; // TODO Change this to a new type or add more info
        }
        return {newBoard, moveResult};

    }else if(pathSize == 2){
        if(PieceMoverAux::isDiagonal(path) && moveResult.status() != Chess::Board::MoveResult::Status::Collision){
            return {originalBoard, Rules::InvalidPieceMovement{originalPosition, finalPosition, pieceDescription}};
        }else if( (pieceDescription.sideSelector() == Chess::Board::SideSelector::Black && path[0].row() < path[1].row() ) ||
                  (pieceDescription.sideSelector() == Chess::Board::SideSelector::White && path[0].row() > path[1].row() )){
            return {originalBoard, Rules::InvalidPieceMovement{originalPosition, finalPosition, pieceDescription}};
        }else if(!PieceMoverAux::isDiagonal(path) && moveResult.status() == Chess::Board::MoveResult::Status::Collision){
            return {originalBoard, Rules::InvalidPieceMovement{originalPosition, finalPosition, pieceDescription}};
        }
        return {newBoard, moveResult};
    }
    return {originalBoard, Rules::InvalidPieceMovement{originalPosition, finalPosition, pieceDescription}};
}

}    
}