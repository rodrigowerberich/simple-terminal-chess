#include "gtest/gtest.h"
#include "BishopMoveRequester.hh"

#define MACRO_P(_C,_R) Chess::Board::Position{Chess::Board::Column::_C, _R}

TEST(BishopMoveRequester, oneHorizontalStepGrowing) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(B,2), MACRO_P(B,3));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, oneHorizontalStepShrinking) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(B,3), MACRO_P(B,2));
    auto correctPath = std::vector<Chess::Board::Position>{};
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, twoHorizontalStepGrowing) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(B,2), MACRO_P(B,4));
    auto correctPath = std::vector<Chess::Board::Position>{};
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, twoHorizontalStepShrinking) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(B,4), MACRO_P(B,2));
    auto correctPath = std::vector<Chess::Board::Position>{};
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, fourHorizontalStepShrinking) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(B,6), MACRO_P(B,2));
    auto correctPath = std::vector<Chess::Board::Position>{};
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, oneVerticalStepGrowing) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(B,3), MACRO_P(C,3));
    auto correctPath = std::vector<Chess::Board::Position>{};
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, oneVerticalStepShrinking) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(C,3), MACRO_P(B,3));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, twoVerticalStepGrowing) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(C,3), MACRO_P(E,3));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, twoVerticalStepShrinking) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(E,3), MACRO_P(C,3));
    auto correctPath = std::vector<Chess::Board::Position>{};
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, fourVerticalStepGrowing) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(B,4), MACRO_P(F,4));
    auto correctPath = std::vector<Chess::Board::Position>{};
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, fourVerticalStepShrinking) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(F,4), MACRO_P(B,4));
    auto correctPath = std::vector<Chess::Board::Position>{};
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, invalidEndVertical) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(B,2), MACRO_P(B,10));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, invalidEndHorizontal) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(B,2), MACRO_P(Invalid,2));
    auto correctPath = std::vector<Chess::Board::Position>{ };
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, diagonalUpperRight) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(B,2), MACRO_P(C,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(C,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, diagonalUpperLeft) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(B,2), MACRO_P(C,1));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(C,1)};
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, diagonalLowerRight) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(B,2), MACRO_P(A,3));
    auto correctPath = std::vector<Chess::Board::Position>{MACRO_P(B,2), MACRO_P(A,3)};
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, diagonalLowerLeft) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(B,2), MACRO_P(A,1));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(A,1) };
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, longerDiagonal1) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(B,2), MACRO_P(D,4));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(B,2), MACRO_P(C,3), MACRO_P(D,4) };
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, longerDiagonal2) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(F,1), MACRO_P(A,6));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(F,1), MACRO_P(E,2), MACRO_P(D,3), MACRO_P(C,4), MACRO_P(B,5), MACRO_P(A,6) };
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, longerDiagonal3) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(C,8), MACRO_P(H,3));
    auto correctPath = std::vector<Chess::Board::Position>{ MACRO_P(C,8), MACRO_P(D,7), MACRO_P(E,6), MACRO_P(F,5), MACRO_P(G,4), MACRO_P(H,3) };
    ASSERT_EQ(path, correctPath);
}

TEST(BishopMoveRequester, random) {
    using namespace Chess::Rules::BishopMoveRequester;
    auto path = bishopPath(MACRO_P(C,3), MACRO_P(E,7));
    auto correctPath = std::vector<Chess::Board::Position>{  };
    ASSERT_EQ(path, correctPath);
}
