#pragma once

#include <map>

#include "Board/PieceDescription.hh"
#include "Board/Side.hh"
#include "Board/MoveResult.hh"

namespace Chess{
namespace Board{

class Board{
    Chess::Board::Side m_whiteSide;
    Chess::Board::Side m_blackSide;
    std::map<Chess::Board::Column, std::map<Chess::Board::Row, Chess::Board::PieceDescription>> m_occupancyMap;
public:
    Board();
    Chess::Board::Position getPiecePosition(const Chess::Board::PieceDescription& pieceDescription) const;
    Chess::Board::PieceDescription getPieceAtPosition(const Chess::Board::Position& position) const;
    Chess::Board::MoveResult movePiece(const Chess::Board::PieceDescription& pieceDescription, const Chess::Board::Position& position);
};

}
}