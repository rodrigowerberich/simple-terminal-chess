#include "gtest/gtest.h"
#include "PieceMoverAux.hh"

#define MACRO_P(_C,_R) Chess::Board::Position{Chess::Board::Column::_C, _R}

TEST(PieceMoverAux, isDiagonal1) {
    auto path = Chess::Rules::PieceMoverAux::Path{MACRO_P(A,1),MACRO_P(B,2)};
    ASSERT_TRUE(Chess::Rules::PieceMoverAux::isDiagonal(path));
}

TEST(PieceMoverAux, isDiagonal2) {
    auto path = Chess::Rules::PieceMoverAux::Path{MACRO_P(A,1),MACRO_P(H,8)};
    ASSERT_TRUE(Chess::Rules::PieceMoverAux::isDiagonal(path));
}

// TODO add more tests here