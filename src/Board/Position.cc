#include "Board/Position.hh"

#include <sstream>

std::ostream& operator<<(std::ostream& os, const Chess::Board::Position& position){
    os << position.toString();
    return os;
}


namespace Chess{
namespace Board{

std::string column_to_string(Column column){
    switch (column){
    case Chess::Board::Column::A :
        return "A";
    case Chess::Board::Column::B :
        return "B";
    case Chess::Board::Column::C :
        return "C";
    case Chess::Board::Column::D :
        return "D";
    case Chess::Board::Column::E :
        return "E";
    case Chess::Board::Column::F :
        return "F";
    case Chess::Board::Column::G :
        return "G";
    case Chess::Board::Column::H :
        return "H";
    default:
        return "Invalid";
    }
}

std::vector<Column> column_as_vector(){
    return {Column::A, Column::B, Column::C, Column::D, Column::E, Column::F, Column::G, Column::H};
}

int column_to_int(Column column){
    switch (column){
    case Chess::Board::Column::A :
        return 1;
    case Chess::Board::Column::B :
        return 2;
    case Chess::Board::Column::C :
        return 3;
    case Chess::Board::Column::D :
        return 4;
    case Chess::Board::Column::E :
        return 5;
    case Chess::Board::Column::F :
        return 6;
    case Chess::Board::Column::G :
        return 7;
    case Chess::Board::Column::H :
        return 8;
    default:
        return 0;
    }
}


Chess::Board::Row Chess::Board::Position::row() const{
    return m_row;
}
Chess::Board::Column Chess::Board::Position::column() const{
    return m_column;
}
bool Chess::Board::Position::isValid() const{
    return (m_row != Chess::Board::Position::INVALID_ROW_VALUE) && (m_column != Chess::Board::Column::Invalid);
}

std::string Chess::Board::Position::toString() const{
    std::stringstream out;
    if(!Chess::Board::Position::isValid()){
        out << "Invalid";
    }else{
        out << column_to_string(m_column);
        out << m_row;
    }
    return out.str();
}

bool Chess::Board::Position::operator==(const Chess::Board::Position& lhs) const{
    return (m_row == lhs.m_row) && (m_column == lhs.m_column);
}



}
} // namespace Chess
