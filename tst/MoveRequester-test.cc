#include "gtest/gtest.h"
#include "MoveRequester.hh"
#include "Board.hh"
#include "BoardDefinitions.hh"
#include "BoardPrinter.hh"

#include <sstream>

static constexpr char NORMAL_BOARD[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA | W-PB | W-PC | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF | W-kG | W-RH |
|______|______|______|______|______|______|______|______|)";

static constexpr char MOVE_REQUESTER_PAWN_VALID_PLAY_ONE_MOVEMENT_STR_1[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      | W-PB |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA |      | W-PC | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF | W-kG | W-RH |
|______|______|______|______|______|______|______|______|)";

TEST(MoveRequester, requestMoveCollision) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pieceDescription = Definitions::W_PB_DESCRIPTION;
    auto position = Chess::Board::Position{Chess::Board::Column::B, 7};
    MoveProposalAnalysis analysis = MoveRequester::proposeMove(board, pieceDescription, position);
    ASSERT_EQ(analysis.type(), MoveProposalAnalysis::Type::MoveResult);
    ASSERT_EQ(analysis.info<MoveResult>().status(), MoveResult::Status::Collision);
    ASSERT_TRUE(analysis.info<MoveResult>().info<MoveResult::Info::Collision>().differentSide);
    ASSERT_FALSE(analysis.info<MoveResult>().info<MoveResult::Info::Collision>().sameSide);
    ASSERT_TRUE(analysis.info<MoveResult>().info<MoveResult::Info::Collision>().originalPiece.isValid());
    ASSERT_EQ(analysis.info<MoveResult>().info<MoveResult::Info::Collision>().originalPiece, pieceDescription);
    ASSERT_TRUE(analysis.info<MoveResult>().info<MoveResult::Info::Collision>().colidingPiece.isValid());
    ASSERT_EQ(analysis.info<MoveResult>().info<MoveResult::Info::Collision>().position, position);

    std::stringstream outputStream;
    outputStream << Chess::Output::BoardPrinter(analysis.board());
    ASSERT_EQ(outputStream.str(), NORMAL_BOARD);
}

TEST(MoveRequester, pawnValidPlayOneMovement) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pieceDescription = Definitions::W_PB_DESCRIPTION;
    auto position = Chess::Board::Position{Chess::Board::Column::B, 3};
    MoveProposalAnalysis analysis = MoveRequester::proposeMove(board, pieceDescription, position);
    ASSERT_EQ(analysis.type(), MoveProposalAnalysis::Type::MoveResult);
    ASSERT_EQ(analysis.info<MoveResult>().status(), MoveResult::Status::Ok);

    std::stringstream outputStream1;
    outputStream1 << Chess::Output::BoardPrinter(board);
    ASSERT_EQ(outputStream1.str(), NORMAL_BOARD);
    std::stringstream outputStream2;
    outputStream2 << Chess::Output::BoardPrinter(analysis.board());
    ASSERT_EQ(outputStream2.str(), MOVE_REQUESTER_PAWN_VALID_PLAY_ONE_MOVEMENT_STR_1);

}