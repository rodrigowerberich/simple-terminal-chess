#include "gtest/gtest.h"
#include "Side.hh"
#include "Piece.hh"

TEST(Side, sideConstruction) {
    using namespace Chess;
    auto side = Board::Side(Board::SideSelector::White);
    auto pieceType = Board::PieceType::Pawn;
    Board::PieceSelector pieceSelector {Board::PieceSelector::Pawn::B};
    auto& piece = side.getPiece(pieceType, pieceSelector);
    std::cout << piece << std::endl;
}