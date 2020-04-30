#pragma once

#include "BoardPosition.hh"

namespace Chess{
namespace Board{

enum class PieceType{
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

class Piece{
private:
    Chess::Board::PieceType m_type;
    Chess::Board::Position m_position;
public:
    Piece(Chess::Board::PieceType type, Chess::Board::Position position = {Chess::Board::Column::Invalid, 0});
    Chess::Board::PieceType type() const;
    const Chess::Board::Position& currentPosition() const;
    void setPosition(const Chess::Board::Position& position);
};

}
}

std::ostream& operator<<(std::ostream& os, const Chess::Board::PieceType& type);
std::ostream& operator<<(std::ostream& os, const Chess::Board::Piece& position);
