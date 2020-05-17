#include "gtest/gtest.h"
#include "QueenMoveRequester.hh"

#define MACRO_P(_C,_R) Chess::Board::Position{Chess::Board::Column::_C, _R}

TEST(QueenMoveRequester, oneHorizontalStepGrowing) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(B,2), MACRO_P(B,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(B,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, oneHorizontalStepShrinking) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(B,3), MACRO_P(B,2));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,3), MACRO_P(B,2) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, twoHorizontalStepGrowing) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(B,2), MACRO_P(B,4));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(B,3), MACRO_P(B,4) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, twoHorizontalStepShrinking) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(B,4), MACRO_P(B,2));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,4), MACRO_P(B,3), MACRO_P(B,2) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, fourHorizontalStepShrinking) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(B,6), MACRO_P(B,2));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,6), MACRO_P(B,5), MACRO_P(B,4), MACRO_P(B,3), MACRO_P(B,2) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, oneVerticalStepGrowing) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(B,3), MACRO_P(C,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,3), MACRO_P(C,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, oneVerticalStepShrinking) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(C,3), MACRO_P(B,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(C,3), MACRO_P(B,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, twoVerticalStepGrowing) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(C,3), MACRO_P(E,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(C,3), MACRO_P(D,3), MACRO_P(E,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, twoVerticalStepShrinking) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(E,3), MACRO_P(C,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(E,3), MACRO_P(D,3), MACRO_P(C,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, fourVerticalStepGrowing) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(B,4), MACRO_P(F,4));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,4), MACRO_P(C,4), MACRO_P(D,4), MACRO_P(E,4), MACRO_P(F,4) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, fourVerticalStepShrinking) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(F,4), MACRO_P(B,4));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(F,4), MACRO_P(E,4), MACRO_P(D,4), MACRO_P(C,4), MACRO_P(B,4) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, invalidEndVertical) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(B,2), MACRO_P(B,10));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, invalidEndHorizontal) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(B,2), MACRO_P(Invalid,2));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, diagonalUpperRight) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(B,2), MACRO_P(C,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(C,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, diagonalUpperLeft) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(B,2), MACRO_P(C,1));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(C,1)};
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, diagonalLowerRight) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(B,2), MACRO_P(A,3));
    auto correctPath = std::vector<Chess::Board::Position>{MACRO_P(B,2), MACRO_P(A,3)};
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, diagonalLowerLeft) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(B,2), MACRO_P(A,1));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(A,1) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, longerDiagonal1) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(B,2), MACRO_P(D,4));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(C,3), MACRO_P(D,4) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, longerDiagonal2) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(F,1), MACRO_P(A,6));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(F,1), MACRO_P(E,2), MACRO_P(D,3), MACRO_P(C,4), MACRO_P(B,5), MACRO_P(A,6) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, longerDiagonal3) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(C,8), MACRO_P(H,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(C,8), MACRO_P(D,7), MACRO_P(E,6), MACRO_P(F,5), MACRO_P(G,4), MACRO_P(H,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(QueenMoveRequester, random) {
    using namespace Chess::Rules::QueenMoveRequester;
    auto path = queenPath(MACRO_P(C,3), MACRO_P(E,7));
    auto correctPath = std::vector<Chess::Board::Position>{  };
    ASSERT_EQ(path, correctPath);
}
