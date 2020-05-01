#include "Board.hh"

namespace Chess{
namespace Board{

Board::Board():
m_whiteSide{Chess::Board::SideSelector::White},
m_blackSide{Chess::Board::SideSelector::Black}{

}
Chess::Board::Position Board::getPiecePosition(const Chess::Board::PieceDescription& pieceDescription) const{
    switch (pieceDescription.sideSelector){
        case Chess::Board::SideSelector::Black: return m_blackSide.getPiece(pieceDescription.type, pieceDescription.pieceSelector).currentPosition();
        case Chess::Board::SideSelector::White: return m_whiteSide.getPiece(pieceDescription.type, pieceDescription.pieceSelector).currentPosition();
        default: return {Chess::Board::Column::Invalid,Chess::Board::Row{0}};
    }
}

}
}