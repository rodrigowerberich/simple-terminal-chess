#pragma once

#include "Piece.hh"
#include "Side.hh"

namespace Chess{
namespace Board{

struct PieceDescription{
    Chess::Board::SideSelector sideSelector;
    Chess::Board::PieceType type;
    Chess::Board::PieceSelector pieceSelector;
};

}
}