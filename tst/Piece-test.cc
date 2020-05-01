// #include <string>
// #include <sstream>
// #include <iostream>
// #include <algorithm>

#include "gtest/gtest.h"
#include "Piece.hh"


TEST(Piece, pieceConstruction) {
    using namespace Chess;
    Board::Position position = {Board::Column::B,3};
    Board::Piece piece = {Board::PieceType::Bishop, position};
    ASSERT_EQ(piece.type(), Board::PieceType::Bishop);
    ASSERT_EQ(piece.currentPosition(),position);
}