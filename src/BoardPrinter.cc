#include <sstream>

#include "BoardPrinter.hh"

namespace Chess{
namespace Output{

BoardPrinter::BoardPrinter(Chess::Board::Board board):
m_board{board}{

}

std::string BoardPrinter::getRow(Board::Row row) const{
    auto columns = Board::column_as_vector();
    std::stringstream ss;
    ss << "|";
    for(const auto& column:columns){
        auto pieceDescription = m_board.getPieceAtPosition({column, row});
        if(pieceDescription.isValid()){
            ss << " " <<  pieceDescription.sideSelector() << "-" << pieceDescription.type() << pieceDescription.pieceSelector().toString(pieceDescription.type()) << " |";
        }else{
            ss << "      |";
        }
    }
    return ss.str();
}


}
}

std::ostream& operator<<(std::ostream& os, const Chess::Output::BoardPrinter& position){
    
    os << position.m_rowTop << "\n";
    for(size_t row = 8; row > 0; row--){
        os << position.m_emptyRow << "\n";
        os << position.getRow(row) << "\n";
        os << position.m_rowBottom;
        if(row > 1){
            os << "\n";
        }
    }
    return os;
}