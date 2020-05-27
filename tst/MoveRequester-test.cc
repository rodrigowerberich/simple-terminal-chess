#include "gtest/gtest.h"
#include "MoveRequester.hh"
#include "Board.hh"
#include "BoardDefinitions.hh"
#include "BoardPrinter.hh"
#include "BoardComparer.hh"

#include <sstream>

#define ASSERT_MOVEMENT_OK(board_, description_, position_, old_position_, boardFinalStatus_)\
{ \
    auto analysisInternalMacro = MoveRequester::proposeMove(board_, description_, position_); \
    ASSERT_EQ(analysisInternalMacro.type(), MoveProposalAnalysis::Type::MoveResult); \
    ASSERT_EQ(analysisInternalMacro.info<MoveResult>().status(), MoveResult::Status::Ok); \
    ASSERT_EQ(analysisInternalMacro.info<MoveResult>().info<MoveResult::Info::Ok>().oldPosition, old_position_); \
    ASSERT_EQ(analysisInternalMacro.info<MoveResult>().info<MoveResult::Info::Ok>().newPosition, position_); \
    ASSERT_TRUE(Comparer::compare(analysisInternalMacro.board(), boardFinalStatus_)); \
    board_ = analysisInternalMacro.board(); \
}

#define ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board_, description_, position_, initial_position_, boardFinalStatus_)\
{ \
    auto analysisInternalMacro = MoveRequester::proposeMove(board_, description_, position_); \
    ASSERT_EQ(analysisInternalMacro.type(), MoveProposalAnalysis::Type::InvalidPieceMovement); \
    ASSERT_EQ(analysisInternalMacro.info<InvalidPieceMovement>().initialPosition, initial_position_); \
    ASSERT_EQ(analysisInternalMacro.info<InvalidPieceMovement>().finalPosition, position_); \
    ASSERT_EQ(analysisInternalMacro.info<InvalidPieceMovement>().pieceDescription, description_); \
    ASSERT_TRUE(Comparer::compare(analysisInternalMacro.board(), boardFinalStatus_)); \
    board_ = analysisInternalMacro.board(); \
}

#define ASSERT_MOVEMENT_COLLISION_SAME_SIDE(board_, description_, position_, colliding_piece_description_ , boardFinalStatus_)\
{ \
    auto analysisInternalMacro = MoveRequester::proposeMove(board_, description_, position_); \
    ASSERT_EQ(analysisInternalMacro.type(), MoveProposalAnalysis::Type::MoveResult); \
    ASSERT_EQ(analysisInternalMacro.info<MoveResult>().status(), MoveResult::Status::Collision); \
    ASSERT_TRUE(analysisInternalMacro.info<MoveResult>().info<MoveResult::Info::Collision>().sameSide); \
    ASSERT_FALSE(analysisInternalMacro.info<MoveResult>().info<MoveResult::Info::Collision>().differentSide); \
    ASSERT_EQ(analysisInternalMacro.info<MoveResult>().info<MoveResult::Info::Collision>().originalPiece, description_); \
    ASSERT_EQ(analysisInternalMacro.info<MoveResult>().info<MoveResult::Info::Collision>().colidingPiece, colliding_piece_description_); \
    ASSERT_EQ(analysisInternalMacro.info<MoveResult>().info<MoveResult::Info::Collision>().position, position_); \
    ASSERT_TRUE(Comparer::compare(analysisInternalMacro.board(), boardFinalStatus_)); \
    board_ = analysisInternalMacro.board(); \
}

#define ASSERT_MOVEMENT_COLLISION_DIFFERENT_SIDE(board_, description_, position_, colliding_piece_description_ , boardFinalStatus_)\
{ \
    auto analysisInternalMacro = MoveRequester::proposeMove(board_, description_, position_); \
    ASSERT_EQ(analysisInternalMacro.type(), MoveProposalAnalysis::Type::MoveResult); \
    ASSERT_EQ(analysisInternalMacro.info<MoveResult>().status(), MoveResult::Status::Collision); \
    ASSERT_FALSE(analysisInternalMacro.info<MoveResult>().info<MoveResult::Info::Collision>().sameSide); \
    ASSERT_TRUE(analysisInternalMacro.info<MoveResult>().info<MoveResult::Info::Collision>().differentSide); \
    ASSERT_EQ(analysisInternalMacro.info<MoveResult>().info<MoveResult::Info::Collision>().originalPiece, description_); \
    ASSERT_EQ(analysisInternalMacro.info<MoveResult>().info<MoveResult::Info::Collision>().colidingPiece, colliding_piece_description_); \
    ASSERT_EQ(analysisInternalMacro.info<MoveResult>().info<MoveResult::Info::Collision>().position, position_); \
    ASSERT_TRUE(Comparer::compare(analysisInternalMacro.board(), boardFinalStatus_)); \
    board_ = analysisInternalMacro.board(); \
}

#define ASSERT_MOVEMENT_INTERRUPTED(board_, description_, position_, initial_position_, collision_position_, colliding_piece_description_, boardFinalStatus_)\
{ \
    auto analysisInternalMacro = MoveRequester::proposeMove(board_, description_, position_); \
    ASSERT_EQ(analysisInternalMacro.type(), MoveProposalAnalysis::Type::MovementInterrupted); \
    ASSERT_EQ(analysisInternalMacro.info<MovementInterrupted>().initialPosition, initial_position_); \
    ASSERT_EQ(analysisInternalMacro.info<MovementInterrupted>().collisionPosition, collision_position_); \
    ASSERT_EQ(analysisInternalMacro.info<MovementInterrupted>().finalPosition, position_); \
    ASSERT_EQ(analysisInternalMacro.info<MovementInterrupted>().pieceDescription, description_); \
    ASSERT_EQ(analysisInternalMacro.info<MovementInterrupted>().pieceInPathDescription, colliding_piece_description_); \
    ASSERT_TRUE(Comparer::compare(analysisInternalMacro.board(), boardFinalStatus_)); \
    board_ = analysisInternalMacro.board(); \
}

#define ASSERT_MOVEMENT_INVALID_INPUT_INVALID_POSITION(board_, description_, position_, boardFinalStatus_)\
{ \
    auto analysisInternalMacro = MoveRequester::proposeMove(board_, description_, position_); \
    ASSERT_EQ(analysisInternalMacro.type(), MoveProposalAnalysis::Type::MoveResult); \
    ASSERT_EQ(analysisInternalMacro.info<MoveResult>().status(), MoveResult::Status::InvalidInput); \
    ASSERT_EQ(analysisInternalMacro.info<MoveResult>().info<MoveResult::Info::InvalidInput>().type , MoveResult::Info::InvalidInput::Type::InvalidPosition);\
    ASSERT_EQ(analysisInternalMacro.info<MoveResult>().info<MoveResult::Info::InvalidInput>().invalidPieceDescription , description_); \
    ASSERT_TRUE(Comparer::compare(analysisInternalMacro.board(), boardFinalStatus_)); \
    board_ = analysisInternalMacro.board(); \
}

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

static constexpr char MOVE_REQUESTER_PAWN_DOUBLE_MOVE_BLACK_STR_1[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB |      | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      | B-PC |      |      |      |      |      |
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

static constexpr char MOVE_REQUESTER_PAWN_FRONTAL_COLISION_1[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB |      | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      | B-PC |      |      |      |      |      |
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

static constexpr char MOVE_REQUESTER_ROOK_DIFFERENT_SIDE_COLLISION_1[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA |      |      |      |      |      |      |      |
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

static constexpr char MOVE_REQUESTER_ROOK_DIFFERENT_SIDE_COLLISION_2[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
|      | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-RA |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA |      |      |      |      |      |      |      |
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

static constexpr char MOVE_REQUESTER_ROOK_DIFFERENT_SIDE_COLLISION_3[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
|      | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      | B-RA |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA |      |      |      |      |      |      |      |
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

static constexpr char MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_1[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA |      | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-kB |      |      |      |      |      |      |      |
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

static constexpr char MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_2[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA |      | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      | B-kB |      |      |      |      |      |
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

static constexpr char MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_3[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA |      | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      | B-kB |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      | W-kG |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA | W-PB | W-PC | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF |      | W-RH |
|______|______|______|______|______|______|______|______|)";

static constexpr char MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_4[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA |      | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      | B-kB |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      | W-kG |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA | W-PB | W-PC | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF |      | W-RH |
|______|______|______|______|______|______|______|______|)";

static constexpr char MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_5[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA |      | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
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
| B-kB |      |      | W-kG |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA | W-PB | W-PC | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF |      | W-RH |
|______|______|______|______|______|______|______|______|)";

static constexpr char MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_6[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA |      | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      | B-kB |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      | W-kG |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA | W-PB | W-PC | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF |      | W-RH |
|______|______|______|______|______|______|______|______|)";

static constexpr char MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_7[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA |      | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      | B-kB |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      | W-kG |      |      |
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
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF |      | W-RH |
|______|______|______|______|______|______|______|______|)";

static constexpr char MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_8[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA |      | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      | B-kB |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      | W-kG |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA | W-PB | W-PC | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF |      | W-RH |
|______|______|______|______|______|______|______|______|)";

static constexpr char MOVE_REQUESTER_KNIGHT_KNIGHT_DIFFERENT_SIDE_COLLISION_1[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA |      | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      | B-kB |      |      |      |      |      |
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

static constexpr char MOVE_REQUESTER_KNIGHT_KNIGHT_DIFFERENT_SIDE_COLLISION_2[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA |      | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
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
|      | B-kB |      |      |      |      |      |      |
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

static constexpr char MOVE_REQUESTER_BISHOP_MOVEMENT_VALID_1_1[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC |      | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      | B-PD |      |      |      |      |
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

static constexpr char MOVE_REQUESTER_BISHOP_MOVEMENT_VALID_1_2[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB |      | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC |      | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      | B-PD |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      | B-BC |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA | W-PB | W-PC | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF | W-kG | W-RH |
|______|______|______|______|______|______|______|______|)";

static constexpr char MOVE_REQUESTER_BISHOP_MOVEMENT_VALID_2_1[] =
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

static constexpr char MOVE_REQUESTER_BISHOP_MOVEMENT_VALID_2_2[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB |      | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA |      | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-BC | B-PB |      |      |      |      |      |      |
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

static constexpr char MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_1_1[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB |      | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      | B-PC |      |      |      |      |      |
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

static constexpr char MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_1_2[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC |      | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB |      | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      | B-Q  |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      | B-PC |      |      |      |      |      |
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

static constexpr char MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_2_1[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD |      | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      | B-PE |      |      |      |
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

static constexpr char MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_2_2[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC |      | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD |      | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      | B-Q  |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      | B-PE |      |      |      |
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

static constexpr char MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_3_1[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC |      | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      | B-PD |      |      |      |      |
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

static constexpr char MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_3_2[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC |      | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC |      | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      | B-Q  |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      | B-PD |      |      |      |      |
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

static constexpr char MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_3_3[] =
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC |      | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC |      | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-Q  |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      | B-PD |      |      |      |      |
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


TEST(MoveRequester, pawnRequestMoveTooBigOfAMovement) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pieceDescription = Definitions::W_PB_DESCRIPTION;
    auto position = Chess::Board::Position{Chess::Board::Column::B, 7};
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, pieceDescription, position, Definitions::W_PB_POSITION, NORMAL_BOARD);
}

TEST(MoveRequester, pawnValidPlayOneMovement) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    ASSERT_TRUE(Comparer::compare(board, NORMAL_BOARD));
    PieceDescription pieceDescription = Definitions::W_PB_DESCRIPTION;
    auto position = Chess::Board::Position{Chess::Board::Column::B, 3};
    ASSERT_MOVEMENT_OK(board, pieceDescription, position, Definitions::W_PB_POSITION, MOVE_REQUESTER_PAWN_VALID_PLAY_ONE_MOVEMENT_STR_1);
}

TEST(MoveRequester, pawnRequestDiagonalNotCollision) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pieceDescription = Definitions::W_PB_DESCRIPTION;
    auto position = Chess::Board::Position{Chess::Board::Column::C, 3};
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, pieceDescription, position, Definitions::W_PB_POSITION, NORMAL_BOARD);
}

TEST(MoveRequester, pawnRequestDiagonalCollisionSameSide) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pcDescription = Definitions::W_PC_DESCRIPTION;
    auto pcPosition = Chess::Board::Position{Chess::Board::Column::C, 3};
    ASSERT_MOVEMENT_OK(board, pcDescription, pcPosition, Definitions::W_PC_POSITION, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_SAME_SIDE_STR_1);

    PieceDescription pbDescription = Definitions::W_PB_DESCRIPTION;
    auto pbPosition = Chess::Board::Position{Chess::Board::Column::C, 3};
    ASSERT_MOVEMENT_COLLISION_SAME_SIDE(board, pbDescription, pbPosition, pcDescription, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_SAME_SIDE_STR_1);
}

TEST(MoveRequester, pawnRequestDiagonalCollisionDifferentSide) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pcDescription = Definitions::W_PC_DESCRIPTION;
    
    // Move W-PC C2->C4
    auto pcPosition1 = Chess::Board::Position{Chess::Board::Column::C, 4};
    ASSERT_MOVEMENT_OK(board, pcDescription, pcPosition1, Definitions::W_PC_POSITION, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_1);

    // Move W-PC C4->C5
    auto pcPosition2 = Chess::Board::Position{Chess::Board::Column::C, 5};
    ASSERT_MOVEMENT_OK(board, pcDescription, pcPosition2, pcPosition1, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_2);

    // Move B-PB B7->B6
    PieceDescription pbDescription = Definitions::B_PB_DESCRIPTION;
    auto pbPosition1 = Chess::Board::Position{Chess::Board::Column::B, 6};
    ASSERT_MOVEMENT_OK(board, pbDescription, pbPosition1, Definitions::B_PB_POSITION, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_3);

    // Move P-PB B6->C5
    auto pbPosition2 = Chess::Board::Position{Chess::Board::Column::C, 5};
    ASSERT_MOVEMENT_COLLISION_DIFFERENT_SIDE(board, pbDescription, pbPosition2, pcDescription, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_3);
}

TEST(MoveRequester, pawnDoubleMoveWhite) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pcDescription = Definitions::W_PC_DESCRIPTION;
    
    // Move W-PC C2->C4
    auto pcPosition1 = Chess::Board::Position{Chess::Board::Column::C, 4};
    ASSERT_MOVEMENT_OK(board, pcDescription, pcPosition1, Definitions::W_PC_POSITION, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_1);
    
    // Move W-PC C4->C6
    auto pcPosition2 = Chess::Board::Position{Chess::Board::Column::C, 6};
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, pcDescription, pcPosition2, pcPosition1, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_1);
}

TEST(MoveRequester, pawnDoubleMoveBlack) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pcDescription = Definitions::B_PC_DESCRIPTION;
    
    // Move B-PC C7->C5
    auto pcPosition1 = Chess::Board::Position{Chess::Board::Column::C, 5};
    ASSERT_MOVEMENT_OK(board, pcDescription, pcPosition1, Definitions::B_PC_POSITION, MOVE_REQUESTER_PAWN_DOUBLE_MOVE_BLACK_STR_1);

    // Move B-PC C5->C3
    auto pcPosition2 = Chess::Board::Position{Chess::Board::Column::C, 3};
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, pcDescription, pcPosition2, pcPosition1, MOVE_REQUESTER_PAWN_DOUBLE_MOVE_BLACK_STR_1);
}

TEST(MoveRequester, pawnVerticalBackMovementWhite) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pcDescription = Definitions::W_PC_DESCRIPTION;
    
    // Move W-PC C2->C4
    auto pcPosition1 = Chess::Board::Position{Chess::Board::Column::C, 4};
    ASSERT_MOVEMENT_OK(board, pcDescription, pcPosition1, Definitions::W_PC_POSITION, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_1);

    // Trying to move W-PC C4->C3
    auto pcPosition2 = Chess::Board::Position{Chess::Board::Column::C, 3};
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, pcDescription, pcPosition2, pcPosition1, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_1);
}

TEST(MoveRequester, pawnVerticalDoubleBackMovementWhite) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pcDescription = Definitions::W_PC_DESCRIPTION;
    
    // Move W-PC C2->C4
    auto pcPosition1 = Chess::Board::Position{Chess::Board::Column::C, 4};
    ASSERT_MOVEMENT_OK(board, pcDescription, pcPosition1, Definitions::W_PC_POSITION, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_1);

    // Trying to move W-PC C4->2
    auto pcPosition2 = Chess::Board::Position{Chess::Board::Column::C, 2};
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, pcDescription, pcPosition2, pcPosition1, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_1);
}

TEST(MoveRequester, pawnVerticalBackMovementBlack) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pcDescription = Definitions::B_PC_DESCRIPTION;
    
    // Move B-PC C7->C5
    auto pcPosition1 = Chess::Board::Position{Chess::Board::Column::C, 5};
    ASSERT_MOVEMENT_OK(board, pcDescription, pcPosition1, Definitions::B_PC_POSITION, MOVE_REQUESTER_PAWN_DOUBLE_MOVE_BLACK_STR_1);

    // Trying to move B-PC C5->C6
    auto pcPosition2 = Chess::Board::Position{Chess::Board::Column::C, 6};
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, pcDescription, pcPosition2, pcPosition1, MOVE_REQUESTER_PAWN_DOUBLE_MOVE_BLACK_STR_1);
}

TEST(MoveRequester, pawnVerticalDoubleBackMovementBlack) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pcDescription = Definitions::B_PC_DESCRIPTION;
    
    // Move B-PC C7->C5
    auto pcPosition1 = Chess::Board::Position{Chess::Board::Column::C, 5};
    ASSERT_MOVEMENT_OK(board, pcDescription, pcPosition1, Definitions::B_PC_POSITION, MOVE_REQUESTER_PAWN_DOUBLE_MOVE_BLACK_STR_1);

    // Trying to move B-PC C5->C7
    auto pcPosition2 = Chess::Board::Position{Chess::Board::Column::C, 7};
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, pcDescription, pcPosition2, pcPosition1, MOVE_REQUESTER_PAWN_DOUBLE_MOVE_BLACK_STR_1);
}

TEST(MoveRequester, pawnInvalidDiagonalMovement) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pcDescription = Definitions::W_PC_DESCRIPTION;
    
    // Move W-PC C2->E4
    auto pcPosition1 = Chess::Board::Position{Chess::Board::Column::E, 4};
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, pcDescription, pcPosition1, Definitions::W_PC_POSITION, NORMAL_BOARD); 
}

TEST(MoveRequester, pawnHorizontalMovementBlack) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pcDescription = Definitions::B_PC_DESCRIPTION;
    
    // Move B-PC C7->C5
    auto pcPosition1 = Chess::Board::Position{Chess::Board::Column::C, 5};
    ASSERT_MOVEMENT_OK(board, pcDescription, pcPosition1, Definitions::B_PC_POSITION, MOVE_REQUESTER_PAWN_DOUBLE_MOVE_BLACK_STR_1);

    // Trying to move B-PC C5->D5
    auto pcPosition2 = Chess::Board::Position{Chess::Board::Column::D, 5};
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, pcDescription, pcPosition2, pcPosition1, MOVE_REQUESTER_PAWN_DOUBLE_MOVE_BLACK_STR_1); 
}

TEST(MoveRequester, pawnHorizontalMovementBlackWithCollision) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pcDescription = Definitions::B_PC_DESCRIPTION;
    
    // Trying to move B-PC C7->D7
    auto pcPosition1 = Chess::Board::Position{Chess::Board::Column::D, 7};
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, pcDescription, pcPosition1, Definitions::B_PC_POSITION, NORMAL_BOARD); 
}

TEST(MoveRequester, pawnFrontalCollisionLarge) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pcDescription = Definitions::W_PC_DESCRIPTION;
    
    // Move W-PC C2->C4
    auto pcPosition1 = Chess::Board::Position{Chess::Board::Column::C, 4};
    ASSERT_MOVEMENT_OK(board, pcDescription, pcPosition1, Definitions::W_PC_POSITION, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_1);

    // Move W-PC C4->C5
    auto pcPosition2 = Chess::Board::Position{Chess::Board::Column::C, 5};
    ASSERT_MOVEMENT_OK(board, pcDescription, pcPosition2, pcPosition1, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_2);

    // Move B-PB C7->C5
    PieceDescription bPcDescription = Definitions::B_PC_DESCRIPTION;
    auto pbPosition1 = Chess::Board::Position{Chess::Board::Column::C, 5};
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, bPcDescription, pbPosition1, Definitions::B_PC_POSITION, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_2);
}

TEST(MoveRequester, pawnFrontalCollision) {
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    PieceDescription pcDescription = Definitions::W_PC_DESCRIPTION;
    
    // Move W-PC C2->C4
    auto pcPosition1 = Chess::Board::Position{Chess::Board::Column::C, 4};
    ASSERT_MOVEMENT_OK(board, pcDescription, pcPosition1, Definitions::W_PC_POSITION, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_1);

    // Move W-PC C4->C5
    auto pcPosition2 = Chess::Board::Position{Chess::Board::Column::C, 5};
    ASSERT_MOVEMENT_OK(board, pcDescription, pcPosition2, pcPosition1, MOVE_REQUESTER_REQUEST_DIAGONAL_COLLISION_DIFFERENT_SIDE_STR_2);

    // Move B-PB C7->C6
    PieceDescription bPcDescription = Definitions::B_PC_DESCRIPTION;
    auto bPcPosition1 = Chess::Board::Position{Chess::Board::Column::C, 6};
    ASSERT_MOVEMENT_OK(board, bPcDescription, bPcPosition1, Definitions::B_PC_POSITION, MOVE_REQUESTER_PAWN_FRONTAL_COLISION_1);

    // Move B-PB C6->C5
    auto bPcPosition2 = Chess::Board::Position{Chess::Board::Column::C, 5};
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, bPcDescription, bPcPosition2, bPcPosition1, MOVE_REQUESTER_PAWN_FRONTAL_COLISION_1);
}

TEST(MoveRequester, rookMovementInterrupted1){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bRADescription = Definitions::B_RA_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::A, 5);
    ASSERT_MOVEMENT_INTERRUPTED(board, bRADescription, position1,  Definitions::B_RA_POSITION,  Definitions::B_PA_POSITION, Definitions::B_PA_DESCRIPTION, NORMAL_BOARD);
}

TEST(MoveRequester, rookMovementInterrupted2){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bRADescription = Definitions::B_RA_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::C, 8);
    ASSERT_MOVEMENT_INTERRUPTED(board, bRADescription, position1,  Definitions::B_RA_POSITION,  Definitions::B_kB_POSITION, Definitions::B_kB_DESCRIPTION, NORMAL_BOARD);
}

TEST(MoveRequester, rookMovementInvalidDiagonal){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bRADescription = Definitions::B_RA_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::B, 7);
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, bRADescription, position1, Definitions::B_RA_POSITION, NORMAL_BOARD); 
}

TEST(MoveRequester, rookSameSideCollision){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bRADescription = Definitions::B_RA_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::A, 7);
    ASSERT_MOVEMENT_COLLISION_SAME_SIDE(board, bRADescription, position1, Definitions::B_PA_DESCRIPTION, NORMAL_BOARD); 
}

TEST(MoveRequester, rookdifferentSideCollision){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bPADescription = Definitions::B_PA_DESCRIPTION;
    auto bPAPosition1 = Chess::Board::Position{Chess::Board::Column::A, 5};
    ASSERT_MOVEMENT_OK(board, bPADescription, bPAPosition1, Definitions::B_PA_POSITION, MOVE_REQUESTER_ROOK_DIFFERENT_SIDE_COLLISION_1);

    auto bRADescription = Definitions::B_RA_DESCRIPTION;
    auto bRAPosition1 = Chess::Board::Position(Chess::Board::Column::A, 6);
    ASSERT_MOVEMENT_OK(board, bRADescription, bRAPosition1, Definitions::B_RA_POSITION, MOVE_REQUESTER_ROOK_DIFFERENT_SIDE_COLLISION_2);


    auto bRAPosition2 = Chess::Board::Position(Chess::Board::Column::D, 6);
    ASSERT_MOVEMENT_OK(board, bRADescription, bRAPosition2, bRAPosition1, MOVE_REQUESTER_ROOK_DIFFERENT_SIDE_COLLISION_3);

    auto bRAPosition3 = Chess::Board::Position(Chess::Board::Column::D, 2);
    ASSERT_MOVEMENT_COLLISION_DIFFERENT_SIDE(board, bRADescription, bRAPosition3, Definitions::W_PD_DESCRIPTION, MOVE_REQUESTER_ROOK_DIFFERENT_SIDE_COLLISION_3); 
}

TEST(MoveRequester, knightValidMovements){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    auto bkBDescription = Definitions::B_kB_DESCRIPTION;
    auto bkBPosition1 = Chess::Board::Position(Chess::Board::Column::A, 6);
    ASSERT_MOVEMENT_OK(board, bkBDescription, bkBPosition1, Definitions::B_kB_POSITION, MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_1);

    auto bkBPosition2 = Chess::Board::Position(Chess::Board::Column::C, 5);
    ASSERT_MOVEMENT_OK(board, bkBDescription, bkBPosition2, bkBPosition1, MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_2);

    auto wkGDescription = Definitions::W_kG_DESCRIPTION;
    auto wkGPosition1 = Chess::Board::Position(Chess::Board::Column::F, 3);
    ASSERT_MOVEMENT_OK(board, wkGDescription, wkGPosition1, Definitions::W_kG_POSITION, MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_3);

    auto wkGPosition2 = Chess::Board::Position(Chess::Board::Column::D, 4);
    ASSERT_MOVEMENT_OK(board, wkGDescription, wkGPosition2, wkGPosition1, MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_4);

    auto bkBPosition3 = Chess::Board::Position(Chess::Board::Column::A, 4);
    ASSERT_MOVEMENT_OK(board, bkBDescription, bkBPosition3, bkBPosition2, MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_5);

    auto bkBPosition4 = Chess::Board::Position(Chess::Board::Column::B, 6);
    ASSERT_MOVEMENT_OK(board, bkBDescription, bkBPosition4, bkBPosition3, MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_6);

    auto wkGPosition3 = Chess::Board::Position(Chess::Board::Column::F, 5);
    ASSERT_MOVEMENT_OK(board, wkGDescription, wkGPosition3, wkGPosition2, MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_7);

    auto wkGPosition4 = Chess::Board::Position(Chess::Board::Column::G, 3);
    ASSERT_MOVEMENT_OK(board, wkGDescription, wkGPosition4, wkGPosition3, MOVE_REQUESTER_KNIGHT_VALID_MOVEMENTS_8);
}

TEST(MoveRequester, knightInvalidMovements1){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    auto bkBDescription = Definitions::B_kB_DESCRIPTION;
    auto bkBPosition1 = Chess::Board::Position(Chess::Board::Column::B, 5);
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, bkBDescription, bkBPosition1, Definitions::B_kB_POSITION, NORMAL_BOARD); 
}

TEST(MoveRequester, knightInvalidMovements2){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    auto bkBDescription = Definitions::B_kB_DESCRIPTION;
    auto bkBPosition1 = Chess::Board::Position(Chess::Board::Column::A, 2);
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, bkBDescription, bkBPosition1, Definitions::B_kB_POSITION, NORMAL_BOARD); 
}

TEST(MoveRequester, knightInvalidMovements3){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    auto bkBDescription = Definitions::B_kB_DESCRIPTION;
    auto bkBPosition1 = Chess::Board::Position(Chess::Board::Column::F, 4);
    ASSERT_MOVEMENT_INVALID_PIECE_MOVEMENT(board, bkBDescription, bkBPosition1, Definitions::B_kB_POSITION, NORMAL_BOARD); 
}

TEST(MoveRequester, knightInvalidMovements4){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    auto bkBDescription = Definitions::B_kB_DESCRIPTION;
    auto bkBPosition1 = Chess::Board::Position(Chess::Board::Column::F, 15);
    ASSERT_MOVEMENT_INVALID_INPUT_INVALID_POSITION(board, bkBDescription, bkBPosition1, NORMAL_BOARD);
}

TEST(MoveRequester, knightInvalidMovements5){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    auto bkBDescription = Definitions::B_kB_DESCRIPTION;
    auto bkBPosition1 = Chess::Board::Position(Chess::Board::Column::Invalid, 5);
    ASSERT_MOVEMENT_INVALID_INPUT_INVALID_POSITION(board, bkBDescription, bkBPosition1, NORMAL_BOARD);
}

TEST(MoveRequester, knightSameSideCollision){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    auto bkBDescription = Definitions::B_kB_DESCRIPTION;
    auto bkBPosition1 = Chess::Board::Position(Chess::Board::Column::D, 7);
    ASSERT_MOVEMENT_COLLISION_SAME_SIDE(board, bkBDescription, bkBPosition1, Definitions::B_PD_DESCRIPTION, NORMAL_BOARD); 
}

TEST(MoveRequester, knightDifferentSideCollision){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    auto bkBDescription = Definitions::B_kB_DESCRIPTION;
    auto bkBPosition1 = Chess::Board::Position(Chess::Board::Column::C, 6);
    ASSERT_MOVEMENT_OK(board, bkBDescription, bkBPosition1, Definitions::B_kB_POSITION, MOVE_REQUESTER_KNIGHT_KNIGHT_DIFFERENT_SIDE_COLLISION_1);

    auto bkBPosition2 = Chess::Board::Position(Chess::Board::Column::B, 4);
    ASSERT_MOVEMENT_OK(board, bkBDescription, bkBPosition2, bkBPosition1, MOVE_REQUESTER_KNIGHT_KNIGHT_DIFFERENT_SIDE_COLLISION_2);

    auto bkBPosition3 = Chess::Board::Position(Chess::Board::Column::C, 2);
    ASSERT_MOVEMENT_COLLISION_DIFFERENT_SIDE(board, bkBDescription, bkBPosition3, Definitions::W_PC_DESCRIPTION, MOVE_REQUESTER_KNIGHT_KNIGHT_DIFFERENT_SIDE_COLLISION_2); 
}

TEST(MoveRequester, bishopMovementInterrupted1){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bBDDescription = Definitions::B_BC_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::E, 6);
    ASSERT_MOVEMENT_INTERRUPTED(board, bBDDescription, position1,  Definitions::B_BC_POSITION,  Definitions::B_PD_POSITION, Definitions::B_PD_DESCRIPTION, NORMAL_BOARD);
}

TEST(MoveRequester, bishopMovementInterrupted2){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bBDDescription = Definitions::B_BC_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::A, 6);
    ASSERT_MOVEMENT_INTERRUPTED(board, bBDDescription, position1,  Definitions::B_BC_POSITION,  Definitions::B_PB_POSITION, Definitions::B_PB_DESCRIPTION, NORMAL_BOARD);
}

TEST(MoveRequester, bishopMovementValid1){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bPDDescription = Definitions::B_PD_DESCRIPTION;
    auto bPDPosition1 = Chess::Board::Position(Chess::Board::Column::D, 6);
    ASSERT_MOVEMENT_OK(board, bPDDescription, bPDPosition1, Definitions::B_PD_POSITION, MOVE_REQUESTER_BISHOP_MOVEMENT_VALID_1_1);

    auto bBDDescription = Definitions::B_BC_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::H, 3);
    ASSERT_MOVEMENT_OK(board, bBDDescription, position1, Definitions::B_BC_POSITION, MOVE_REQUESTER_BISHOP_MOVEMENT_VALID_1_2);
}

TEST(MoveRequester, bishopMovementValid2){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bPDDescription = Definitions::B_PB_DESCRIPTION;
    auto bPDPosition1 = Chess::Board::Position(Chess::Board::Column::B, 6);
    ASSERT_MOVEMENT_OK(board, bPDDescription, bPDPosition1, Definitions::B_PB_POSITION, MOVE_REQUESTER_BISHOP_MOVEMENT_VALID_2_1);

    auto bBDDescription = Definitions::B_BC_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::A, 6);
    ASSERT_MOVEMENT_OK(board, bBDDescription, position1, Definitions::B_BC_POSITION, MOVE_REQUESTER_BISHOP_MOVEMENT_VALID_2_2);
}

TEST(MoveRequester, bishopSameSideCollision){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;
    auto bBDDescription = Definitions::B_BC_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::B, 7);
    ASSERT_MOVEMENT_COLLISION_SAME_SIDE(board, bBDDescription, position1, Definitions::B_PB_DESCRIPTION, NORMAL_BOARD); 
}

TEST(MoveRequester, bishopDifferentSideCollision){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bPDDescription = Definitions::B_PB_DESCRIPTION;
    auto bPDPosition1 = Chess::Board::Position(Chess::Board::Column::B, 6);
    ASSERT_MOVEMENT_OK(board, bPDDescription, bPDPosition1, Definitions::B_PB_POSITION, MOVE_REQUESTER_BISHOP_MOVEMENT_VALID_2_1);

    auto bBDDescription = Definitions::B_BC_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::A, 6);
    ASSERT_MOVEMENT_OK(board, bBDDescription, position1, Definitions::B_BC_POSITION, MOVE_REQUESTER_BISHOP_MOVEMENT_VALID_2_2);

    auto position2 = Chess::Board::Position(Chess::Board::Column::E, 2);
    ASSERT_MOVEMENT_COLLISION_DIFFERENT_SIDE(board, bBDDescription, position2, Definitions::W_PE_DESCRIPTION, MOVE_REQUESTER_BISHOP_MOVEMENT_VALID_2_2); 
}

TEST(MoveRequester, queenMovementInterrupted1){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bQDDescription = Definitions::B_QD_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::F, 6);
    ASSERT_MOVEMENT_INTERRUPTED(board, bQDDescription, position1,  Definitions::B_QD_POSITION,  Definitions::B_PE_POSITION, Definitions::B_PE_DESCRIPTION, NORMAL_BOARD);
}


TEST(MoveRequester, queenMovementInterrupted2){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bQDDescription = Definitions::B_QD_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::B, 6);
    ASSERT_MOVEMENT_INTERRUPTED(board, bQDDescription, position1,  Definitions::B_QD_POSITION,  Definitions::B_PC_POSITION, Definitions::B_PC_DESCRIPTION, NORMAL_BOARD);
}

TEST(MoveRequester, queenMovementInterrupted3){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bQDDescription = Definitions::B_QD_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::D, 6);
    ASSERT_MOVEMENT_INTERRUPTED(board, bQDDescription, position1,  Definitions::B_QD_POSITION,  Definitions::B_PD_POSITION, Definitions::B_PD_DESCRIPTION, NORMAL_BOARD);
}

TEST(MoveRequester, queenMovementInterrupted4){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bQDDescription = Definitions::B_QD_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::B, 8);
    ASSERT_MOVEMENT_INTERRUPTED(board, bQDDescription, position1,  Definitions::B_QD_POSITION,  Definitions::B_BC_POSITION, Definitions::B_BC_DESCRIPTION, NORMAL_BOARD);
}

TEST(MoveRequester, queenMovementInterrupted5){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bQDDescription = Definitions::B_QD_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::F, 8);
    ASSERT_MOVEMENT_INTERRUPTED(board, bQDDescription, position1,  Definitions::B_QD_POSITION,  Definitions::B_KE_POSITION, Definitions::B_KE_DESCRIPTION, NORMAL_BOARD);
}

TEST(MoveRequester, queenMovementMovementValid1){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bPCDescription = Definitions::B_PC_DESCRIPTION;
    auto bPCPosition1 = Chess::Board::Position(Chess::Board::Column::C, 5);
    ASSERT_MOVEMENT_OK(board, bPCDescription, bPCPosition1, Definitions::B_PC_POSITION, MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_1_1);

    auto bQDDescription = Definitions::B_QD_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::B, 6);
    ASSERT_MOVEMENT_OK(board, bQDDescription, position1, Definitions::B_QD_POSITION, MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_1_2);
}


TEST(MoveRequester, queenMovementMovementValid2){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bPCDescription = Definitions::B_PE_DESCRIPTION;
    auto bPCPosition1 = Chess::Board::Position(Chess::Board::Column::E, 5);
    ASSERT_MOVEMENT_OK(board, bPCDescription, bPCPosition1, Definitions::B_PE_POSITION, MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_2_1);

    auto bQDDescription = Definitions::B_QD_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::F, 6);
    ASSERT_MOVEMENT_OK(board, bQDDescription, position1, Definitions::B_QD_POSITION, MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_2_2);
}

TEST(MoveRequester, queenMovementMovementValid3){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bPCDescription = Definitions::B_PD_DESCRIPTION;
    auto bPCPosition1 = Chess::Board::Position(Chess::Board::Column::D, 5);
    ASSERT_MOVEMENT_OK(board, bPCDescription, bPCPosition1, Definitions::B_PD_POSITION, MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_3_1);

    auto bQDDescription = Definitions::B_QD_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::D, 6);
    ASSERT_MOVEMENT_OK(board, bQDDescription, position1, Definitions::B_QD_POSITION, MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_3_2);

    auto position2 = Chess::Board::Position(Chess::Board::Column::A, 6);
    ASSERT_MOVEMENT_OK(board, bQDDescription, position2, position1, MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_3_3);
}

TEST(MoveRequester, queenSameSideCollision){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bQDDescription = Definitions::B_QD_DESCRIPTION;
    auto bQDPosition1 = Chess::Board::Position(Chess::Board::Column::D, 7);
    ASSERT_MOVEMENT_COLLISION_SAME_SIDE(board, bQDDescription, bQDPosition1, Definitions::B_PD_DESCRIPTION, NORMAL_BOARD);
}

TEST(MoveRequester, queenDifferentSideCollision){
    using namespace Chess::Board;
    using namespace Chess::Rules;

    Board board;

    auto bPDDescription = Definitions::B_PD_DESCRIPTION;
    auto bPDPosition1 = Chess::Board::Position(Chess::Board::Column::D, 5);
    ASSERT_MOVEMENT_OK(board, bPDDescription, bPDPosition1, Definitions::B_PD_POSITION, MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_3_1);

    auto bQDDescription = Definitions::B_QD_DESCRIPTION;
    auto position1 = Chess::Board::Position(Chess::Board::Column::D, 6);
    ASSERT_MOVEMENT_OK(board, bQDDescription, position1, Definitions::B_QD_POSITION, MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_3_2);

    auto position2 = Chess::Board::Position(Chess::Board::Column::A, 6);
    ASSERT_MOVEMENT_OK(board, bQDDescription, position2, position1, MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_3_3);

    auto position3 = Chess::Board::Position(Chess::Board::Column::A, 2);
    ASSERT_MOVEMENT_COLLISION_DIFFERENT_SIDE(board, bQDDescription, position3, Definitions::W_PA_DESCRIPTION, MOVE_REQUESTER_QUEEN_MOVEMENT_VALID_3_3);
}