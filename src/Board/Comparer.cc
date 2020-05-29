#include <sstream>

#include "Board/Comparer.hh"
#include "Output/BoardPrinter.hh"

namespace Chess{
namespace Board{
namespace Comparer{

bool compare(const Chess::Board::Board& board1, const Chess::Board::Board& board2){
    std::stringstream board2Stream;
    board2Stream << Chess::Output::BoardPrinter(board2);
    return compare(board1, board2Stream.str());
}
bool compare(const Chess::Board::Board& board, const std::string& boardRepresentation){
    std::stringstream boardStream;
    boardStream << Chess::Output::BoardPrinter(board);
    return compare(boardStream.str(), boardRepresentation);
}
bool compare(const std::string& boardRepresentation, const Chess::Board::Board& board){
    return compare(board, boardRepresentation);
}
bool compare(const std::string& boardRepresentation1, const std::string& boardRepresentation2){
    return boardRepresentation1 == boardRepresentation2;
}


}
}
}