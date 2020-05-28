#pragma once

#include <vector>

#include "BoardPosition.hh"

namespace Chess{
namespace Rules{
namespace KingMoveRequester{

std::vector<Chess::Board::Position> kingPath(const Chess::Board::Position& initialPosition, const Chess::Board::Position& finallPosition);

}
}
}