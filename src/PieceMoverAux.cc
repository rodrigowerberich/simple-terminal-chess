#include "PieceMoverAux.hh"

namespace Chess{
namespace Rules{
namespace PieceMoverAux{

bool isDiagonal(const Path& path){
    if(path.size() < 2){
        // No diagonal with only one element
        return false;
    }
    auto slope = 0;
    for(size_t i=0; i < path.size()-1; i++){
        auto p1 = InternalPosition(path[i]);
        auto p2 = InternalPosition(path[i+1]);
        auto deltaColumn = p2.column() - p1.column();
        auto deltaRow = p2.row() - p1.row();
        if(deltaRow == 0){
            return false;
        }
        auto thisSlope = deltaColumn/deltaRow;
        if(std::abs(thisSlope) != 1){
            return false;
        }
        if(i==0){
            slope = thisSlope;
        }
        if(slope != thisSlope){
            return false;
        }
        slope = thisSlope;
    }
    return true;
}

Board::Column columnFromNumber(int i){
    switch(i){
        case 1: return Board::Column::A;
        case 2: return Board::Column::B;
        case 3: return Board::Column::C;
        case 4: return Board::Column::D;
        case 5: return Board::Column::E;
        case 6: return Board::Column::F;
        case 7: return Board::Column::G;
        case 8: return Board::Column::H;
        default: return Board::Column::Invalid;
    }
}


bool isDiagonal(const ExternalPosition& p1, const ExternalPosition& p2){
    return isDiagonal({p1, p2});
}


int manhattanDistance(const ExternalPosition& inputP1, const ExternalPosition& inputP2){
    auto p1 = InternalPosition(inputP1);
    auto p2 = InternalPosition(inputP2);

    auto deltaColumn = p2.column() - p1.column();
    auto deltaRow = p2.row() - p1.row();

    auto distance = std::abs(deltaColumn) + std::abs(deltaRow);
    return distance;
}


}
}
}