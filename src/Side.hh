#pragma once
#include <map>

#include "Piece.hh"

namespace Chess{
namespace Board{

enum class SideSelector{
    Black,
    White
};

class Side{
private:
    Chess::Board::SideSelector m_sideSelected;
    std::map<Chess::Board::PieceType,std::vector<Board::Piece>> m_pieces;
    static constexpr int WHITE_BACK_ROW = 1;
    static constexpr int WHITE_FRONT_ROW = 2;
    static constexpr int BLACK_BACK_ROW = 8;
    static constexpr int BLACK_FRONT_ROW = 7;
    Board::Piece m_invalidPiece;
public:
    Side(Board::SideSelector sideSelected);
    Board::Piece& getPiece(PieceType type, const PieceSelector& pieceSelector);
};

}
}