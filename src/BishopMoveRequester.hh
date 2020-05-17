#pragma once

#include <vector>

#include "BoardPosition.hh"

namespace Chess{
namespace Rules{
namespace BishopMoveRequester{

std::vector<Chess::Board::Position> bishopPath(const Chess::Board::Position& initialPosition, const Chess::Board::Position& finallPosition);


}
}
}