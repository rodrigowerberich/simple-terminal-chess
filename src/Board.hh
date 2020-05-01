#pragma once

#include "PieceDescription.hh"
#include "Side.hh"
#include "MoveResult.hh"

namespace Chess{
namespace Board{

class Board{
    Chess::Board::Side m_whiteSide;
    Chess::Board::Side m_blackSide;
public:
    Board();
    Chess::Board::Position getPiecePosition(const Chess::Board::PieceDescription& pieceDescription) const;
    Chess::Board::MoveResult movePiece(const Chess::Board::PieceDescription& pieceDescription, const Chess::Board::Position& position);
};

}
}