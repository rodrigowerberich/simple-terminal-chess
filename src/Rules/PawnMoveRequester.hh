#pragma once

#include <vector>

#include "Board/Position.hh"

namespace Chess{
namespace Rules{
namespace PawnMoveRequester{

std::vector<Chess::Board::Position> pawnPath(const Chess::Board::Position& initialPosition, const Chess::Board::Position& finallPosition);


}
}
}