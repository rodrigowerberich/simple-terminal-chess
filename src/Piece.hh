#pragma once

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

struct Piece{
    Chess::Board::PieceType type;
};

}
}