#include "Board.hh"

namespace Chess{
namespace Board{

Board::Board():
m_whiteSide{Chess::Board::SideSelector::White},
m_blackSide{Chess::Board::SideSelector::Black}{

}
Chess::Board::Position Board::getPiecePosition(const Chess::Board::PieceDescription& pieceDescription) const{
    switch (pieceDescription.sideSelector()){
        case Chess::Board::SideSelector::Black: return m_blackSide.getPiece(pieceDescription.type(), pieceDescription.pieceSelector()).currentPosition();
        case Chess::Board::SideSelector::White: return m_whiteSide.getPiece(pieceDescription.type(), pieceDescription.pieceSelector()).currentPosition();
        default: return {Chess::Board::Column::Invalid,Chess::Board::Row{0}};
    }
}

Chess::Board::MoveResult Board::movePiece(const Chess::Board::PieceDescription& pieceDescription, const Chess::Board::Position& newPosition){
    auto& side = (pieceDescription.sideSelector() == SideSelector::White)?m_whiteSide:m_blackSide;
    if(!pieceDescription.isValid()){
        return MoveResult{MoveResult::Status::InvalidInput, {{MoveResult::Info::InvalidInput::Type::InvalidPieceSelector, pieceDescription}}};
    }
    
    auto& piece = side.getPiece(pieceDescription.type(), pieceDescription.pieceSelector());
    if(piece.isValid()){
        auto oldPosition = piece.currentPosition();
        piece.setPosition(newPosition);
        return MoveResult{MoveResult::Status::Ok,{{oldPosition, newPosition}}};
    }else{
        return MoveResult{MoveResult::Status::InvalidInput, {{MoveResult::Info::InvalidInput::Type::InvalidPieceSelector, pieceDescription}}};
    }
}

}
}