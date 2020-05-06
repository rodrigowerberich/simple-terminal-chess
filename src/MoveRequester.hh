#pragma once

#include "Board.hh"
#include "MoveProposalAnalysis.hh"

namespace Chess{
namespace Rules{

class MoveRequester{
using BoardType = Chess::Board::Board;
using PieceDescriptionType = Chess::Board::PieceDescription;
using PositionType = Chess::Board::Position;
using MoveResultType = Chess::Board::MoveResult;
template<Chess::Board::PieceType X> static MoveProposalAnalysis verifyMove(const BoardType& originalBoard, const BoardType& newBoard, const PieceDescriptionType& pieceDescription, const MoveResultType& moveResult);
static MoveProposalAnalysis verifyMove(const BoardType& originalBoard, const BoardType& newBoard, const PieceDescriptionType& pieceDescription, const MoveResultType& moveResult);
public:
static MoveProposalAnalysis proposeMove(const BoardType& board, const PieceDescriptionType& pieceDescription, PositionType position);
};

}
}