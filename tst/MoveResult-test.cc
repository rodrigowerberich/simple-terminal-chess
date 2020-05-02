#include "gtest/gtest.h"
#include "MoveResult.hh"

TEST(MoveResult, OkContruction) {
    using namespace Chess;
    Board::Position oldPosition = {Board::Column::A, 2};
    Board::Position newPosition = {Board::Column::A, 3};
    Board::MoveResult moveResult{Board::MoveResult::Status::Ok,{{oldPosition, newPosition}}};
    ASSERT_EQ(moveResult.status(),Board::MoveResult::Status::Ok);
    ASSERT_EQ(moveResult.info<Board::MoveResult::Info::Ok>().oldPosition, oldPosition);
    ASSERT_EQ(moveResult.info<Board::MoveResult::Info::Ok>().newPosition, newPosition);
}