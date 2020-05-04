#include "MoveProposalAnalysis.hh"

namespace Chess{
namespace Rules{

MoveProposalAnalysis::MoveProposalAnalysis(const Chess::Board::Board& board):m_board{board}, m_type{MoveProposalAnalysis::Type::Invalid}, m_info{0}{
}
MoveProposalAnalysis::MoveProposalAnalysis(const Chess::Board::Board& board, Chess::Board::MoveResult moveResult):m_board{board}, m_type{MoveProposalAnalysis::Type::MoveResult},m_info{moveResult}{
}

const Chess::Board::Board& MoveProposalAnalysis::board(){
    return m_board;
}


const MoveProposalAnalysis::Type& MoveProposalAnalysis::type() const{
    return m_type;
}

template<>
const Chess::Board::MoveResult& MoveProposalAnalysis::info(){
    return m_info.moveResult;
}


}
}