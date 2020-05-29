#include "gtest/gtest.h"
#include "Rules/RookMoveRequester.hh"

#define MACRO_P(_C,_R) Chess::Board::Position{Chess::Board::Column::_C, _R}

TEST(RookMoveRequester, oneHorizontalStepGrowing) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(B,2), MACRO_P(B,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(B,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, oneHorizontalStepShrinking) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(B,3), MACRO_P(B,2));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,3), MACRO_P(B,2) };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, twoHorizontalStepGrowing) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(B,2), MACRO_P(B,4));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(B,3), MACRO_P(B,4) };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, twoHorizontalStepShrinking) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(B,4), MACRO_P(B,2));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,4), MACRO_P(B,3), MACRO_P(B,2) };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, fourHorizontalStepShrinking) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(B,6), MACRO_P(B,2));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,6), MACRO_P(B,5), MACRO_P(B,4), MACRO_P(B,3), MACRO_P(B,2) };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, oneVerticalStepGrowing) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(B,3), MACRO_P(C,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,3), MACRO_P(C,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, oneVerticalStepShrinking) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(C,3), MACRO_P(B,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(C,3), MACRO_P(B,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, twoVerticalStepGrowing) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(C,3), MACRO_P(E,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(C,3), MACRO_P(D,3), MACRO_P(E,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, twoVerticalStepShrinking) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(E,3), MACRO_P(C,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(E,3), MACRO_P(D,3), MACRO_P(C,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, fourVerticalStepGrowing) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(B,4), MACRO_P(F,4));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,4), MACRO_P(C,4), MACRO_P(D,4), MACRO_P(E,4), MACRO_P(F,4) };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, fourVerticalStepShrinking) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(F,4), MACRO_P(B,4));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(F,4), MACRO_P(E,4), MACRO_P(D,4), MACRO_P(C,4), MACRO_P(B,4) };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, invalidEndVertical) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(B,2), MACRO_P(B,10));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, invalidEndHorizontal) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(B,2), MACRO_P(Invalid,2));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, diagonalUpperRight) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(B,2), MACRO_P(C,3));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, diagonalUpperLeft) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(B,2), MACRO_P(C,1));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, diagonalLowerRight) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(B,2), MACRO_P(A,3));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, diagonalLowerLeft) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(B,2), MACRO_P(A,1));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, longerDiagonal) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(B,2), MACRO_P(D,4));
    auto correctPath = std::vector<Chess::Board::Position>{  };
    ASSERT_EQ(path, correctPath);
}

TEST(RookMoveRequester, random) {
    using namespace Chess::Rules::RookMoveRequester;
    auto path = rookPath(MACRO_P(C,3), MACRO_P(E,7));
    auto correctPath = std::vector<Chess::Board::Position>{  };
    ASSERT_EQ(path, correctPath);
}
