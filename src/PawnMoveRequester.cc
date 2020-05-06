#include "MoveRequester.hh"
#include "PawnMoveRequester.hh"

#include <iostream>
namespace Chess{
namespace Rules{
namespace PawnMoveRequester{


bool isDiagonal(int x1, int y1, int x2, int y2){
    auto deltaX = x2-x1;
    auto deltaY = y2-y1;
    auto growthRate = deltaY/deltaX;
    return std::abs(growthRate) == 1;
}

bool isDiagonal(std::vector<Board::Position> path){
    if(path.size() != 2){
        return false;
    }
    auto& initialPosition = path[0];
    auto& finalPosition = path[1];
    auto initialRow = initialPosition.row();
    auto initialColumn = Chess::Board::column_to_int(initialPosition.column());
    auto finalRow = finalPosition.row();
    auto finalColumn = Chess::Board::column_to_int(finalPosition.column());;
    return isDiagonal(initialRow, initialColumn, finalRow, finalColumn);
}

int manhattanDistance(int x1, int y1, int x2, int y2){
    auto deltaX = x2-x1;
    auto deltaY = y2-y1;
    auto distance = std::abs(deltaX) + std::abs(deltaY);
    return distance;
}

std::vector<Chess::Board::Position> pawnPath(const Chess::Board::Position& initialPosition, const Chess::Board::Position& finalPosition){
    std::vector<Chess::Board::Position> path;
    if(!initialPosition.isValid() || !finalPosition.isValid()){
        return path;
    }
    auto initialRow = initialPosition.row();
    auto initialColumn = Chess::Board::column_to_int(initialPosition.column());
    auto finalRow = finalPosition.row();
    auto finalColumn = Chess::Board::column_to_int(finalPosition.column());;

    // Normal pawn movement is only in the same column
    if(initialPosition.column() == finalPosition.column()){
        auto smallToBig = initialRow < finalRow;
        auto distance = std::abs(finalRow - initialRow);
        for(auto index = 0; index <= distance; index++ ){
            auto row = initialRow + index*(smallToBig?1:-1);
            path.push_back({initialPosition.column(), row});
        }
    }else if(isDiagonal(initialRow, initialColumn, finalRow, finalColumn) && (manhattanDistance(initialRow, initialColumn, finalRow, finalColumn) == 2)){
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
        auto pieceAtMiddleDescription = originalBoard.getPieceAtPosition(path[1]);
        if(!pieceAtMiddleDescription.isValid()){
            return {originalBoard, Rules::InvalidPieceMovement{originalPosition, finalPosition, pieceDescription}}; // TODO Change this to a new type
        }
        return {newBoard, moveResult};

    }else if(pathSize == 2){
        if(PawnMoveRequester::isDiagonal(path) && moveResult.status() != Chess::Board::MoveResult::Status::Collision){
            return {originalBoard, Rules::InvalidPieceMovement{originalPosition, finalPosition, pieceDescription}};
        }
        return {newBoard, moveResult};
    }
    return {originalBoard};
}

}    
}