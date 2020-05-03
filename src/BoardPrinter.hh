#pragma once

#include "Board.hh"
#include <ostream>
#include <string>

// Forward declaration for friending operator <<
namespace Chess{
namespace Output{
class BoardPrinter;
}
}

// Forward declaration for friending operator <<
std::ostream& operator<<(std::ostream& os, const Chess::Output::BoardPrinter& position);

namespace Chess{
namespace Output{

class BoardPrinter{
private:
    Chess::Board::Board m_board;
    std::string m_rowTop =    " ______ ______ ______ ______ ______ ______ ______ ______ ";
    std::string m_emptyRow =  "|      |      |      |      |      |      |      |      |";
    std::string m_rowBottom = "|______|______|______|______|______|______|______|______|";
    std::string getRow(Board::Row row) const;
public:
    BoardPrinter(Chess::Board::Board);
    friend std::ostream& ::operator<<(std::ostream& os, const Chess::Output::BoardPrinter& position);
};

}
}