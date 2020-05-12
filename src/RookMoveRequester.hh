#pragma once

#include <vector>

#include "BoardPosition.hh"

namespace Chess{
namespace Rules{
namespace RookMoveRequester{

std::vector<Chess::Board::Position> rookPath(const Chess::Board::Position& initialPosition, const Chess::Board::Position& finallPosition);


}
}
}