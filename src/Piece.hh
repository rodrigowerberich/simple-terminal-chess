#pragma once

#include "BoardPosition.hh"
#include <vector>

namespace Chess{
namespace Board{

enum class PieceType{
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

union PieceSelector{
    enum class Pawn{
        A,B,C,D,E,F,G,H
    };
    enum class Rook {
        A,H
    };
    enum class Knight {
        B,G
    };
    enum class Bishop {
        C,F
    };
    enum class King {
        D
    };
    enum class Queen {
        E
    };
    PieceSelector::Pawn pawn;
    PieceSelector::Rook rook;
    PieceSelector::Knight knight;
    PieceSelector::Bishop bishop;
    PieceSelector::Queen queen;
    PieceSelector::King king;
    PieceSelector(PieceSelector::Pawn inputPawn){
        pawn = inputPawn;
    }
    PieceSelector(PieceSelector::Rook inputRook){
        rook = inputRook;
    }
    PieceSelector(PieceSelector::Knight inputKnight){
        knight = inputKnight;
    }
    PieceSelector(PieceSelector::Bishop inputBishop){
        bishop = inputBishop;
    }
    PieceSelector(PieceSelector::Queen inputQueen){
        queen = inputQueen;
    }
    PieceSelector(PieceSelector::King inputKing){
        king = inputKing;
    }
    template <PieceType t, typename T>
    static int toIndex(T);
    int toIndex(PieceType type) const;
};



std::vector<Chess::Board::PieceType> PieceType_asVector();

class Piece{
private:
    Chess::Board::PieceType m_type;
    Chess::Board::Position m_position;
public:
    Piece(Chess::Board::PieceType type, Chess::Board::Position position = {Chess::Board::Column::Invalid, 0});
    Chess::Board::PieceType type() const;
    const Chess::Board::Position& currentPosition() const;
    void setPosition(const Chess::Board::Position& position);
};

}
}

std::ostream& operator<<(std::ostream& os, const Chess::Board::PieceType& type);
std::ostream& operator<<(std::ostream& os, const Chess::Board::Piece& position);

