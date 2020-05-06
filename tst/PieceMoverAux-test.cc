#include "gtest/gtest.h"
#include "PieceMoverAux.hh"

#define MACRO_P(_C,_R) Chess::Board::Position{Chess::Board::Column::_C, _R}

TEST(PieceMoverAux, isDiagonalUpperRight) {
    auto path = Chess::Rules::PieceMoverAux::Path{MACRO_P(A,1),MACRO_P(B,2)};
    ASSERT_TRUE(Chess::Rules::PieceMoverAux::isDiagonal(path));
}

TEST(PieceMoverAux, isDiagonalUpperLeft) {
    auto path = Chess::Rules::PieceMoverAux::Path{MACRO_P(B,1),MACRO_P(A,2)};
    ASSERT_TRUE(Chess::Rules::PieceMoverAux::isDiagonal(path));
}

TEST(PieceMoverAux, isDiagonalLowerLeft) {
    auto path = Chess::Rules::PieceMoverAux::Path{MACRO_P(B,2),MACRO_P(A,1)};
    ASSERT_TRUE(Chess::Rules::PieceMoverAux::isDiagonal(path));
}

TEST(PieceMoverAux, isDiagonalLowerRight) {
    auto path = Chess::Rules::PieceMoverAux::Path{MACRO_P(B,2),MACRO_P(C,1)};
    ASSERT_TRUE(Chess::Rules::PieceMoverAux::isDiagonal(path));
}

TEST(PieceMoverAux, isDiagonal3) {
    auto path = Chess::Rules::PieceMoverAux::Path{MACRO_P(A,1),MACRO_P(B,2),MACRO_P(C,3),MACRO_P(D,4),
                                                  MACRO_P(E,5),MACRO_P(F,6),MACRO_P(G,7),MACRO_P(H,8)};
    ASSERT_TRUE(Chess::Rules::PieceMoverAux::isDiagonal(path));
}

TEST(PieceMoverAux, isNotDiagonal) {
    auto path = Chess::Rules::PieceMoverAux::Path{MACRO_P(A,1), MACRO_P(B,2), MACRO_P(A,3)};
    ASSERT_FALSE(Chess::Rules::PieceMoverAux::isDiagonal(path));
}

TEST(PieceMoverAux, distanceOf2Number1) {
    auto d = Chess::Rules::PieceMoverAux::manhattanDistance(MACRO_P(A,1), MACRO_P(A,3));
    ASSERT_EQ(d, 2);
}

TEST(PieceMoverAux, distanceOf2Number2) {
    auto d = Chess::Rules::PieceMoverAux::manhattanDistance(MACRO_P(A,1), MACRO_P(C,1));
    ASSERT_EQ(d, 2);
}

TEST(PieceMoverAux, distanceOf2Number3) {
    auto d = Chess::Rules::PieceMoverAux::manhattanDistance(MACRO_P(D,3), MACRO_P(C,2));
    ASSERT_EQ(d, 2);
}

TEST(PieceMoverAux, distanceOf2Number4) {
    auto d = Chess::Rules::PieceMoverAux::manhattanDistance(MACRO_P(E,3), MACRO_P(F,4));
    ASSERT_EQ(d, 2);
}
