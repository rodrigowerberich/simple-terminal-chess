#pragma once

#include <memory>

#include "Board/Board.hh"

namespace Chess{
namespace Rules{

struct InvalidPieceMovement{
    Board::Position initialPosition;
    Board::Position finalPosition;
    Board::PieceDescription pieceDescription;
};

struct MovementInterrupted{
    Board::Position initialPosition;
    Board::Position collisionPosition;
    Board::Position finalPosition;
    Board::PieceDescription pieceDescription;
    Board::PieceDescription pieceInPathDescription;
};

class MoveProposalAnalysis{
public:
    enum class Type{
        MoveResult,
        InvalidPieceMovement,
        MovementInterrupted,
        Invalid
    };
    union Info{
        Chess::Board::MoveResult moveResult;
        int invalid;
        Chess::Rules::MovementInterrupted movementInterrupted;
        Chess::Rules::InvalidPieceMovement invalidPieceMovement;
        Info(Chess::Board::MoveResult moveResult):moveResult{moveResult}{}
        Info(Chess::Rules::MovementInterrupted movementInterrupted):movementInterrupted{movementInterrupted}{}
        Info(Chess::Rules::InvalidPieceMovement invalidPieceMovement):invalidPieceMovement{invalidPieceMovement}{}
        Info(int i):invalid{i}{}
    };
    MoveProposalAnalysis(const Chess::Board::Board& board);
    MoveProposalAnalysis(const Chess::Board::Board& board, Chess::Board::MoveResult moveResult);
    MoveProposalAnalysis(const Chess::Board::Board& board, Chess::Rules::MovementInterrupted movementInterrupted);
    MoveProposalAnalysis(const Chess::Board::Board& board, Chess::Rules::InvalidPieceMovement invalidPieceMovement);
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