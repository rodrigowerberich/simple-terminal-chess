#pragma once

#include <string>

#include "Board/Board.hh"

namespace Chess{
namespace Board{
namespace Comparer{

bool compare(const Chess::Board::Board& board1, const Chess::Board::Board& board2);
bool compare(const Chess::Board::Board& board, const std::string& boardRepresentation);
bool compare(const std::string& boardRepresentation, const Chess::Board::Board& board);
bool compare(const std::string& boardRepresentation1, const std::string& boardRepresentation2);

 
}
}
}