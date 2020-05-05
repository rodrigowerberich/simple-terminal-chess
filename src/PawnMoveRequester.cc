#include "MoveRequester.hh"
#include "PawnMoveRequester.hh"

namespace Chess{
namespace Rules{
namespace PawnMoveRequester{

bool isDiagonal(int x1, int y1, int x2, int y2){
    auto deltaX = x2-x1;
    auto deltaY = y2-y1;
    auto growthRate = deltaY/deltaX;
    return std::abs(growthRate) == 1;
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

    auto b1 = isDiagonal(initialRow, initialColumn, finalRow, finalColumn);
    auto b2 = (manhattanDistance(initialRow, initialColumn, finalRow, finalColumn) == 2);

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
MoveProposalAnalysis MoveRequester::verifyMove<Chess::Board::PieceType::Pawn>(const BoardType& originalBoard, const BoardType& newBoard, const PieceDescriptionType& pieceDescription){
    auto originalPosition = originalBoard.getPiecePosition(pieceDescription);
    auto finalPosition = newBoard.getPiecePosition(pieceDescription);
    auto path = PawnMoveRequester::pawnPath(originalPosition, finalPosition);
    if(path.size() > 4){
        return ;
    }
    return {originalBoard};
}

}    
}