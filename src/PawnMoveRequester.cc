#include "MoveRequester.hh"
#include "PawnMoveRequester.hh"

namespace Chess{
namespace Rules{
namespace PawnMoveRequester{

std::vector<Chess::Board::Position> pawnPath(const Chess::Board::Position& initialPosition, const Chess::Board::Position& finallPosition){
    std::vector<Chess::Board::Position> path;
    if(!initialPosition.isValid() || !finallPosition.isValid()){
        return path;
    }
    if(initialPosition.column() == finallPosition.column()){
        auto initialRow = initialPosition.row();
        auto finalRow = finallPosition.row();
        auto smallToBig = initialRow < finalRow;
        auto distance = std::abs(finalRow - initialRow);
        for(auto index = 0; index <= distance; index++ ){
            auto row = initialRow + index*(smallToBig?1:-1);
            path.push_back({initialPosition.column(), row});
        }
    }
    return path;
}

}

template <>
MoveProposalAnalysis MoveRequester::verifyMove<Chess::Board::PieceType::Pawn>(const BoardType& originalBoard, const BoardType& newBoard, const PieceDescriptionType& pieceDescription){
    auto originalPosition = originalBoard.getPiecePosition(pieceDescription);
    auto finalPosition = newBoard.getPiecePosition(pieceDescription);

    return {originalBoard};
}

}    
}