#include "gtest/gtest.h"
#include "PawnMoveRequester.hh"

#define MACRO_P(_C,_R) Chess::Board::Position{Chess::Board::Column::_C, _R}

TEST(PawnMoveRequester, oneHorizontalStepGrowing) {
    using namespace Chess::Rules::PawnMoveRequester;
    auto path = pawnPath(MACRO_P(B,2), MACRO_P(B,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(B,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(PawnMoveRequester, oneHorizontalStepShrinking) {
    using namespace Chess::Rules::PawnMoveRequester;
    auto path = pawnPath(MACRO_P(B,3), MACRO_P(B,2));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,3), MACRO_P(B,2) };
    ASSERT_EQ(path, correctPath);
}

TEST(PawnMoveRequester, twoHorizontalStepGrowing) {
    using namespace Chess::Rules::PawnMoveRequester;
    auto path = pawnPath(MACRO_P(B,2), MACRO_P(B,4));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(B,3), MACRO_P(B,4) };
    ASSERT_EQ(path, correctPath);
}

TEST(PawnMoveRequester, twoHorizontalStepShrinking) {
    using namespace Chess::Rules::PawnMoveRequester;
    auto path = pawnPath(MACRO_P(B,4), MACRO_P(B,2));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,4), MACRO_P(B,3), MACRO_P(B,2) };
    ASSERT_EQ(path, correctPath);
}

TEST(PawnMoveRequester, fourHorizontalStepShrinking) {
    using namespace Chess::Rules::PawnMoveRequester;
    auto path = pawnPath(MACRO_P(B,6), MACRO_P(B,2));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,6), MACRO_P(B,5), MACRO_P(B,4), MACRO_P(B,3), MACRO_P(B,2) };
    ASSERT_EQ(path, correctPath);
}

TEST(PawnMoveRequester, invalidEnd) {
    using namespace Chess::Rules::PawnMoveRequester;
    auto path = pawnPath(MACRO_P(B,2), MACRO_P(B,10));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(PawnMoveRequester, diagonalUpperRight) {
    using namespace Chess::Rules::PawnMoveRequester;
    auto path = pawnPath(MACRO_P(B,2), MACRO_P(C,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(C,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(PawnMoveRequester, diagonalUpperLeft) {
    using namespace Chess::Rules::PawnMoveRequester;
    auto path = pawnPath(MACRO_P(B,2), MACRO_P(C,1));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(C,1) };
    ASSERT_EQ(path, correctPath);
}

TEST(PawnMoveRequester, diagonalLowerRight) {
    using namespace Chess::Rules::PawnMoveRequester;
    auto path = pawnPath(MACRO_P(B,2), MACRO_P(A,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(A,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(PawnMoveRequester, diagonalLowerLeft) {
    using namespace Chess::Rules::PawnMoveRequester;
    auto path = pawnPath(MACRO_P(B,2), MACRO_P(A,1));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(A,1) };
    ASSERT_EQ(path, correctPath);
}

TEST(PawnMoveRequester, longerDiagonal) {
    using namespace Chess::Rules::PawnMoveRequester;
    auto path = pawnPath(MACRO_P(B,2), MACRO_P(D,4));
    auto correctPath = std::vector<Chess::Board::Position>{  };
    ASSERT_EQ(path, correctPath);
}

TEST(PawnMoveRequester, random) {
    using namespace Chess::Rules::PawnMoveRequester;
    auto path = pawnPath(MACRO_P(C,3), MACRO_P(E,7));
    auto correctPath = std::vector<Chess::Board::Position>{  };
    ASSERT_EQ(path, correctPath);
}
