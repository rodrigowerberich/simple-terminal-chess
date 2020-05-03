#pragma once
#include <map>
#include <ostream>

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
    std::map<Chess::Board::PieceType,std::vector<Chess::Board::Piece>> m_pieces;
    static constexpr int WHITE_BACK_ROW = 1;
    static constexpr int WHITE_FRONT_ROW = 2;
    static constexpr int BLACK_BACK_ROW = 8;
    static constexpr int BLACK_FRONT_ROW = 7;
    Chess::Board::Piece m_invalidPiece;
public:
    Side(Chess::Board::SideSelector sideSelected);
    Chess::Board::Piece& getPiece(PieceType type, const PieceSelector& pieceSelector);
    const Chess::Board::Piece& getPiece(PieceType type, const PieceSelector& pieceSelector) const;

};

}
}

std::ostream& operator<<(std::ostream& os, const Chess::Board::SideSelector& sideSelector);