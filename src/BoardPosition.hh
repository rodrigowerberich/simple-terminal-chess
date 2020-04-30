#pragma once

#include <string>

namespace Chess{
namespace Board{

using Row = int;

enum class Column{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    Invalid
};

std::string column_to_string(Column column);

class Position{
private:
    Chess::Board::Column m_column;
    Chess::Board::Row m_row;
    static constexpr int MAX_ROW = 8;
    static constexpr int MIN_ROW = 1;
    static constexpr int INVALID_ROW_VALUE = 0;
public:
    Position(Chess::Board::Column, Chess::Board::Row row);
    Chess::Board::Row row() const;
    Chess::Board::Column column() const;
    bool isValid() const;
    std::string toString() const;
};

}
}
std::ostream& operator<<(std::ostream& os, const Chess::Board::Position& position);