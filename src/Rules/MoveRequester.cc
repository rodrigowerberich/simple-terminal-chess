#include "Rules/MoveRequester.hh"

#include "Output/BoardPrinter.hh"
#include <iostream>

namespace Chess{
namespace Rules{

MoveProposalAnalysis MoveRequester::verifyMove(const BoardType& originalBoard, const BoardType& newBoard, const PieceDescriptionType& pieceDescription, const MoveResultType& moveResult){
    switch(pieceDescription.type()){
        case Chess::Board::PieceType::Pawn: return verifyMove<Chess::Board::PieceType::Pawn>(originalBoard, newBoard, pieceDescription, moveResult);
        case Chess::Board::PieceType::Rook: return verifyMove<Chess::Board::PieceType::Rook>(originalBoard, newBoard, pieceDescription, moveResult);
        case Chess::Board::PieceType::Knight: return verifyMove<Chess::Board::PieceType::Knight>(originalBoard, newBoard, pieceDescription, moveResult);
        case Chess::Board::PieceType::Bishop: return verifyMove<Chess::Board::PieceType::Bishop>(originalBoard, newBoard, pieceDescription, moveResult);
        case Chess::Board::PieceType::Queen: return verifyMove<Chess::Board::PieceType::Queen>(originalBoard, newBoard, pieceDescription, moveResult);
        case Chess::Board::PieceType::King: return verifyMove<Chess::Board::PieceType::King>(originalBoard, newBoard, pieceDescription, moveResult);
        default: return {originalBoard};
    }
}

MoveProposalAnalysis MoveRequester::proposeMove(const BoardType& board, const PieceDescriptionType& pieceDescription, PositionType position){
    BoardType newBoard = board;
    auto initialMoveResult = newBoard.movePiece(pieceDescription, position);
    
    if( initialMoveResult.status() == Chess::Board::MoveResult::Status::InvalidInput || 
        initialMoveResult.status() == Chess::Board::MoveResult::Status::NoMovement){
        return MoveProposalAnalysis{board, initialMoveResult};
    }
    return verifyMove(board, newBoard, pieceDescription, initialMoveResult);
}

}
}