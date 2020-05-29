#pragma once

#include <vector>

#include "Board/Position.hh"

namespace Chess{
namespace Rules{
namespace QueenMoveRequester{

std::vector<Chess::Board::Position> queenPath(const Chess::Board::Position& initialPosition, const Chess::Board::Position& finallPosition);

}
}
}