#pragma once

#include <vector>

#include "BoardPosition.hh"

namespace Chess{
namespace Rules{
namespace PieceMoverAux{

using Path = std::vector<Chess::Board::Position>;
using ExternalPosition = Chess::Board::Position;

struct InternalPosition{
private:
    int m_column;
    int m_row;
public:
    constexpr InternalPosition(const ExternalPosition& position):m_column{0},m_row{0}{
        if(position.isValid()){
            m_column = Chess::Board::column_to_int(position.column());
            m_row = position.row();
        }
    }
    constexpr int column() const{ return m_column; }
    constexpr int row() const{ return m_row; }
    constexpr bool isValid() const { return (m_row != 0) && (m_column != 0); }
};

bool isDiagonal(const Path& path);
bool isDiagonal(const ExternalPosition& p1, const ExternalPosition& p2);
int manhattanDistance(const ExternalPosition& p1, const ExternalPosition& p2);

}
}
}