#include "gtest/gtest.h"
#include "KingMoveRequester.hh"

#define MACRO_P(_C,_R) Chess::Board::Position{Chess::Board::Column::_C, _R}

TEST(KingMoveRequester, oneHorizontalStepGrowing) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(B,2), MACRO_P(B,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(B,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, oneHorizontalStepShrinking) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(B,3), MACRO_P(B,2));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,3), MACRO_P(B,2) };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, twoHorizontalStepGrowing) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(B,2), MACRO_P(B,4));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, twoHorizontalStepShrinking) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(B,4), MACRO_P(B,2));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, fourHorizontalStepShrinking) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(B,6), MACRO_P(B,2));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, oneVerticalStepGrowing) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(B,3), MACRO_P(C,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,3), MACRO_P(C,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, oneVerticalStepShrinking) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(C,3), MACRO_P(B,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(C,3), MACRO_P(B,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, twoVerticalStepGrowing) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(C,3), MACRO_P(E,3));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, twoVerticalStepShrinking) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(E,3), MACRO_P(C,3));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, fourVerticalStepGrowing) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(B,4), MACRO_P(F,4));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, fourVerticalStepShrinking) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(F,4), MACRO_P(B,4));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, invalidEndVertical) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(B,2), MACRO_P(B,10));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, invalidEndHorizontal) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(B,2), MACRO_P(Invalid,2));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, diagonalUpperRight) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(B,2), MACRO_P(C,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(C,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, diagonalUpperLeft) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(B,2), MACRO_P(C,1));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(C,1)};
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, diagonalLowerRight) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(B,2), MACRO_P(A,3));
    auto correctPath = std::vector<Chess::Board::Position>{MACRO_P(B,2), MACRO_P(A,3)};
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, diagonalLowerLeft) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(B,2), MACRO_P(A,1));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(A,1) };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, longerDiagonal1) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(B,2), MACRO_P(D,4));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, longerDiagonal2) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(F,1), MACRO_P(A,6));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, longerDiagonal3) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(C,8), MACRO_P(H,3));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(KingMoveRequester, random) {
    using namespace Chess::Rules::KingMoveRequester;
    auto path = kingPath(MACRO_P(C,3), MACRO_P(E,7));
    auto correctPath = std::vector<Chess::Board::Position>{  };
    ASSERT_EQ(path, correctPath);
}
