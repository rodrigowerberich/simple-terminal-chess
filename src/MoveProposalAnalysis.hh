#pragma once

#include "Board.hh"

namespace Chess{
namespace Rules{

class MoveProposalAnalysis{
public:
    enum class Type{
        MoveResult,
        Invalid
    };
    union Info{
        Chess::Board::MoveResult moveResult;
        int invalid;
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