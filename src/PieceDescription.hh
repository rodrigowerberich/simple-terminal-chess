#pragma once

#include "Piece.hh"
#include "Side.hh"

namespace Chess{
namespace Board{

class PieceDescription{
private:
    Chess::Board::SideSelector m_sideSelector;
    Chess::Board::PieceType m_type;
    Chess::Board::PieceSelector m_pieceSelector;
    Chess::Board::PieceType m_pieceSelectorType;
public:
    PieceDescription();
    PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceType pieceType, Chess::Board::PieceSelector::Pawn pawnSelector);
    PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceType pieceType, Chess::Board::PieceSelector::Rook rookSelector);
    PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceType pieceType, Chess::Board::PieceSelector::Knight knightSelector);
    PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceType pieceType, Chess::Board::PieceSelector::Bishop bishopSelector);
    PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceType pieceType, Chess::Board::PieceSelector::Queen queenSelector);
    PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceType pieceType, Chess::Board::PieceSelector::King kingSelector);
    Chess::Board::SideSelector sideSelector() const;
    Chess::Board::PieceType type() const;
    Chess::Board::PieceSelector pieceSelector() const;
    Chess::Board::PieceType pieceSelectorType() const;
    bool isValid() const;
    bool operator==(const PieceDescription& rhs) const;
};

}
}