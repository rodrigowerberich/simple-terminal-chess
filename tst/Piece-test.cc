#include "gtest/gtest.h"
#include "Piece.hh"


TEST(Piece, pieceConstruction) {
    using namespace Chess;
    Board::Position position = {Board::Column::B,3};
    Board::Piece piece = {Board::PieceType::Bishop, position};
    ASSERT_EQ(piece.type(), Board::PieceType::Bishop);
    ASSERT_EQ(piece.currentPosition(),position);
}

TEST(Piece, defaultConstructor){
    using namespace Chess;

    auto pieceTypes = Board::PieceType_asVector();
    for(auto pieceType:pieceTypes){
        auto piece = Board::Piece{pieceType};
        ASSERT_EQ(pieceType, piece.type());
        ASSERT_FALSE(piece.currentPosition().isValid());
    }
}

TEST(Piece, changePosition) {
    using namespace Chess;
    Board::Position position = {Board::Column::D,2};
    Board::Position newPosition = {Board::Column::E,3};
    Board::Piece piece = {Board::PieceType::Bishop, position};
    ASSERT_EQ(piece.currentPosition(),position);
    piece.setPosition(newPosition);
    ASSERT_EQ(piece.currentPosition(), newPosition);
}