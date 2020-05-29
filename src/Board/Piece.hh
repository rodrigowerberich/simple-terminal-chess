#pragma once

#include "Board/Position.hh"
#include <vector>

namespace Chess{
namespace Board{

enum class PieceType{
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King,
    Invalid
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
    enum class Queen {
        D
    };
    enum class King {
        E
    };
    PieceSelector::Pawn pawn;
    PieceSelector::Rook rook;
    PieceSelector::Knight knight;
    PieceSelector::Bishop bishop;
    PieceSelector::Queen queen;
    PieceSelector::King king;
    constexpr PieceSelector(PieceSelector::Pawn inputPawn):pawn{inputPawn}{}
    constexpr PieceSelector(PieceSelector::Rook inputRook):rook{inputRook}{}
    constexpr PieceSelector(PieceSelector::Knight inputKnight):knight{inputKnight}{}
    constexpr PieceSelector(PieceSelector::Bishop inputBishop):bishop{inputBishop}{}
    constexpr PieceSelector(PieceSelector::Queen inputQueen):queen{inputQueen}{}
    constexpr PieceSelector(PieceSelector::King inputKing):king{inputKing}{}
    template <PieceType t, typename T>
    static int toIndex(T);
    int toIndex(PieceType type) const;
    template <PieceType t, typename T>
    static std::string toString(T);
    std::string toString(PieceType type) const;

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
    bool isValid() const;
    bool isOnBoard() const;
};

}
}

std::ostream& operator<<(std::ostream& os, const Chess::Board::PieceType& type);
std::ostream& operator<<(std::ostream& os, const Chess::Board::Piece& position);

