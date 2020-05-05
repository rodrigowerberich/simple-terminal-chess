#pragma once

#include <memory>

#include "Board.hh"

namespace Chess{
namespace Rules{

struct InvalidPieceMovement{
    Board::Position initialPosition;
    Board::Position finalPosition;
    Board::PieceDescription pieceDescription;
};


class MoveProposalAnalysis{
public:
    enum class Type{
        MoveResult,
        InvalidPieceMovement,
        Invalid
    };
    union Info{
        // InvalidPieceMovement create Invalid piece movement class
        Chess::Board::MoveResult moveResult;
        int invalid;
        Chess::Rules::InvalidPieceMovement invalidPieceMovement;
        Info(Chess::Board::MoveResult moveResult):moveResult{moveResult}{}
        Info(int i):invalid{i}{}
    };
    MoveProposalAnalysis(const Chess::Board::Board& board);
    MoveProposalAnalysis(const Chess::Board::Board& board, Chess::Board::MoveResult moveResult);
    const Chess::Board::Board& board();
    const MoveProposalAnalysis::Type& type() const;
    template<typename T>
    const T& info();

private:
    Chess::Board::Board m_board;
    MoveProposalAnalysis::Type m_type;
    MoveProposalAnalysis::Info m_info;
};

}
}