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

static constexpr char MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_SAME_SIDE_STR_1[] =
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
|      |      | W-PC |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA | W-PB |      | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF | W-kG | W-RH |
|______|______|______|______|______|______|______|______|)";

static constexpr char MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_1[] =
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
|      |      | W-PC |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA | W-PB |      | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF | W-kG | W-RH |
|______|______|______|______|______|______|______|______|)";

static constexpr char MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_2[] =
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
|      |      | W-PC |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA | W-PB |      | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF | W-kG | W-RH |
|______|______|______|______|______|______|______|______|)";

static constexpr char MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_3[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA |      | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      | B-PB |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      | W-PC |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA | W-PB |      | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF | W-kG | W-RH |
|______|______|______|______|______|______|______|______|)";

TEST(MoveRequester, requestMoveToBigOfAMovement) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pieceDescription = Definitions::W_PB_DESCRIPTION;
    auto position = Chess::Board::Position{Chess::Board::Column::B, 7};
    MoveProposalAnalysis analysis = MoveRequester::proposeMove(board, pieceDescription, position);
    ASSERT_EQ(analysis.type(), MoveProposalAnalysis::Type::InvalidPieceMovement);
    ASSERT_EQ(analysis.info<InvalidPieceMovement>().initialPosition, Definitions::W_PB_POSITION);
    ASSERT_EQ(analysis.info<InvalidPieceMovement>().finalPosition, position);
    ASSERT_EQ(analysis.info<InvalidPieceMovement>().pieceDescription, Definitions::W_PB_DESCRIPTION);
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

TEST(MoveRequester, requestDiagonalNotCollision) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pieceDescription = Definitions::W_PB_DESCRIPTION;
    auto position = Chess::Board::Position{Chess::Board::Column::C, 3};
    MoveProposalAnalysis analysis = MoveRequester::proposeMove(board, pieceDescription, position);
    ASSERT_EQ(analysis.type(), MoveProposalAnalysis::Type::InvalidPieceMovement);
    ASSERT_EQ(analysis.info<InvalidPieceMovement>().initialPosition, Definitions::W_PB_POSITION);
    ASSERT_EQ(analysis.info<InvalidPieceMovement>().finalPosition, position);
    ASSERT_EQ(analysis.info<InvalidPieceMovement>().pieceDescription, Definitions::W_PB_DESCRIPTION);
    std::stringstream outputStream;
    outputStream << Chess::Output::BoardPrinter(analysis.board());
    ASSERT_EQ(outputStream.str(), NORMAL_BOARD);
}

TEST(MoveRequester, requestDiagonalCollisionSameSide) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pcDescription = Definitions::W_PC_DESCRIPTION;
    auto pcPosition = Chess::Board::Position{Chess::Board::Column::C, 3};
    MoveProposalAnalysis analysis1 = MoveRequester::proposeMove(board, pcDescription, pcPosition);
    ASSERT_EQ(analysis1.type(), MoveProposalAnalysis::Type::MoveResult);
    ASSERT_EQ(analysis1.info<MoveResult>().status(), MoveResult::Status::Ok);
    board = analysis1.board();

    std::stringstream outputStream;
    outputStream << Chess::Output::BoardPrinter(analysis1.board());
    ASSERT_EQ(outputStream.str(), MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_SAME_SIDE_STR_1);


    PieceDescription pbDescription = Definitions::W_PB_DESCRIPTION;
    auto pbPosition = Chess::Board::Position{Chess::Board::Column::C, 3};
    MoveProposalAnalysis analysis2 = MoveRequester::proposeMove(board, pbDescription, pbPosition);
    ASSERT_EQ(analysis2.type(), MoveProposalAnalysis::Type::MoveResult);
    ASSERT_EQ(analysis2.info<MoveResult>().status(), MoveResult::Status::Collision);
    ASSERT_TRUE(analysis2.info<MoveResult>().info<MoveResult::Info::Collision>().sameSide);
    ASSERT_EQ(analysis2.info<MoveResult>().info<MoveResult::Info::Collision>().originalPiece, pbDescription);
    ASSERT_EQ(analysis2.info<MoveResult>().info<MoveResult::Info::Collision>().colidingPiece, pcDescription);
    ASSERT_EQ(analysis2.info<MoveResult>().info<MoveResult::Info::Collision>().position, pbPosition);
    ASSERT_EQ(pbPosition, pcPosition);
 
    std::stringstream outputStream2;
    outputStream2 << Chess::Output::BoardPrinter(analysis2.board());
    ASSERT_EQ(outputStream2.str(), MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_SAME_SIDE_STR_1);
}

TEST(MoveRequester, requestDiagonalCollisionDifferentSide) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pcDescription = Definitions::W_PC_DESCRIPTION;
    
    // Move W-PC C2->C4
    auto pcPosition1 = Chess::Board::Position{Chess::Board::Column::C, 4};
    MoveProposalAnalysis analysis1 = MoveRequester::proposeMove(board, pcDescription, pcPosition1);
    ASSERT_EQ(analysis1.type(), MoveProposalAnalysis::Type::MoveResult);
    ASSERT_EQ(analysis1.info<MoveResult>().status(), MoveResult::Status::Ok);
    board = analysis1.board();

    std::stringstream outputStream;
    outputStream << Chess::Output::BoardPrinter(analysis1.board());
    ASSERT_EQ(outputStream.str(), MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_1);
    outputStream.str("");

    // Move W-PC C4->C5
    auto pcPosition2 = Chess::Board::Position{Chess::Board::Column::C, 5};
    MoveProposalAnalysis analysis2 = MoveRequester::proposeMove(board, pcDescription, pcPosition2);
    ASSERT_EQ(analysis2.type(), MoveProposalAnalysis::Type::MoveResult);
    ASSERT_EQ(analysis2.info<MoveResult>().status(), MoveResult::Status::Ok);
    board = analysis2.board();

    outputStream << Chess::Output::BoardPrinter(analysis2.board());
    ASSERT_EQ(outputStream.str(), MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_2);
    outputStream.str("");


    // Move B-PB B7->B6
    PieceDescription pbDescription = Definitions::B_PB_DESCRIPTION;
    auto pbPosition1 = Chess::Board::Position{Chess::Board::Column::B, 6};
    MoveProposalAnalysis analysis3 = MoveRequester::proposeMove(board, pbDescription, pbPosition1);
    ASSERT_EQ(analysis3.type(), MoveProposalAnalysis::Type::MoveResult);
    ASSERT_EQ(analysis3.info<MoveResult>().status(), MoveResult::Status::Ok);
    board = analysis3.board();

    outputStream << Chess::Output::BoardPrinter(analysis3.board());
    ASSERT_EQ(outputStream.str(), MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_3);
    outputStream.str("");

    // Move P-PB B6->C5
    auto pbPosition2 = Chess::Board::Position{Chess::Board::Column::C, 5};
    MoveProposalAnalysis analysis4 = MoveRequester::proposeMove(board, pbDescription, pbPosition2);
    ASSERT_EQ(analysis4.type(), MoveProposalAnalysis::Type::MoveResult);
    ASSERT_EQ(analysis4.info<MoveResult>().status(), MoveResult::Status::Collision);
    ASSERT_TRUE(analysis4.info<MoveResult>().info<MoveResult::Info::Collision>().differentSide);
    ASSERT_EQ(analysis4.info<MoveResult>().info<MoveResult::Info::Collision>().originalPiece, pbDescription);
    ASSERT_EQ(analysis4.info<MoveResult>().info<MoveResult::Info::Collision>().colidingPiece, pcDescription);
    ASSERT_EQ(analysis4.info<MoveResult>().info<MoveResult::Info::Collision>().position, pbPosition2);
    ASSERT_EQ(pbPosition2, pcPosition2);
    board = analysis4.board();

    outputStream << Chess::Output::BoardPrinter(analysis4.board());
    ASSERT_EQ(outputStream.str(), MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_3);
    outputStream.str("");
}

// Add double space pawn moving checking, Add horizontal moving checker and backward moving checker