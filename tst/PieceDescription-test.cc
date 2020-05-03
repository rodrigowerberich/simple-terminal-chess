#include "gtest/gtest.h"
#include "PieceDescription.hh"

TEST(PieceDescription, pawnA) {
    using namespace Chess::Board;
    auto pawnADescription = PieceDescription{SideSelector::White, PieceSelector::Pawn::A};    
    ASSERT_TRUE(pawnADescription.isValid());
    ASSERT_EQ(pawnADescription.sideSelector(), SideSelector::White);
    ASSERT_EQ(pawnADescription.type(), PieceType::Pawn);
    ASSERT_EQ(pawnADescription.pieceSelector().pawn, PieceSelector::Pawn::A);
    ASSERT_EQ(pawnADescription.pieceSelectorType(), PieceType::Pawn);
}
TEST(PieceDescription, pawnB) {
    using namespace Chess::Board;
    auto pawnBDescription = PieceDescription{SideSelector::Black, PieceSelector::Pawn::B};    
    ASSERT_TRUE(pawnBDescription.isValid());
    ASSERT_EQ(pawnBDescription.sideSelector(), SideSelector::Black);
    ASSERT_EQ(pawnBDescription.type(), PieceType::Pawn);
    ASSERT_EQ(pawnBDescription.pieceSelector().pawn, PieceSelector::Pawn::B);
    ASSERT_EQ(pawnBDescription.pieceSelectorType(), PieceType::Pawn);
}
TEST(PieceDescription, pawnC) {
    using namespace Chess::Board;
    auto pawnCDescription = PieceDescription{SideSelector::White, PieceSelector::Pawn::C};    
    ASSERT_TRUE(pawnCDescription.isValid());
    ASSERT_EQ(pawnCDescription.sideSelector(), SideSelector::White);
    ASSERT_EQ(pawnCDescription.type(), PieceType::Pawn);
    ASSERT_EQ(pawnCDescription.pieceSelector().pawn, PieceSelector::Pawn::C);
    ASSERT_EQ(pawnCDescription.pieceSelectorType(), PieceType::Pawn);
}
TEST(PieceDescription, pawnD) {
    using namespace Chess::Board;
    auto pawnDDescription = PieceDescription{SideSelector::Black, PieceSelector::Pawn::D};    
    ASSERT_TRUE(pawnDDescription.isValid());
    ASSERT_EQ(pawnDDescription.sideSelector(), SideSelector::Black);
    ASSERT_EQ(pawnDDescription.type(), PieceType::Pawn);
    ASSERT_EQ(pawnDDescription.pieceSelector().pawn, PieceSelector::Pawn::D);
    ASSERT_EQ(pawnDDescription.pieceSelectorType(), PieceType::Pawn);
}
TEST(PieceDescription, pawnE) {
    using namespace Chess::Board;
    auto pawnEDescription = PieceDescription{SideSelector::White, PieceSelector::Pawn::E};    
    ASSERT_TRUE(pawnEDescription.isValid());
    ASSERT_EQ(pawnEDescription.sideSelector(), SideSelector::White);
    ASSERT_EQ(pawnEDescription.type(), PieceType::Pawn);
    ASSERT_EQ(pawnEDescription.pieceSelector().pawn, PieceSelector::Pawn::E);
    ASSERT_EQ(pawnEDescription.pieceSelectorType(), PieceType::Pawn);
}
TEST(PieceDescription, pawnF) {
    using namespace Chess::Board;
    auto pawnFDescription = PieceDescription{SideSelector::Black, PieceSelector::Pawn::F};    
    ASSERT_TRUE(pawnFDescription.isValid());
    ASSERT_EQ(pawnFDescription.sideSelector(), SideSelector::Black);
    ASSERT_EQ(pawnFDescription.type(), PieceType::Pawn);
    ASSERT_EQ(pawnFDescription.pieceSelector().pawn, PieceSelector::Pawn::F);
    ASSERT_EQ(pawnFDescription.pieceSelectorType(), PieceType::Pawn);
}
TEST(PieceDescription, pawnG) {
    using namespace Chess::Board;   
    auto pawnGDescription = PieceDescription{SideSelector::White, PieceSelector::Pawn::G};    
    ASSERT_TRUE(pawnGDescription.isValid());
    ASSERT_EQ(pawnGDescription.sideSelector(), SideSelector::White);
    ASSERT_EQ(pawnGDescription.type(), PieceType::Pawn);
    ASSERT_EQ(pawnGDescription.pieceSelector().pawn, PieceSelector::Pawn::G);
    ASSERT_EQ(pawnGDescription.pieceSelectorType(), PieceType::Pawn);
}
TEST(PieceDescription, pawnH) {
    using namespace Chess::Board;   
    auto pawnHDescription = PieceDescription{SideSelector::Black, PieceSelector::Pawn::H};    
    ASSERT_TRUE(pawnHDescription.isValid());
    ASSERT_EQ(pawnHDescription.sideSelector(), SideSelector::Black);
    ASSERT_EQ(pawnHDescription.type(), PieceType::Pawn);
    ASSERT_EQ(pawnHDescription.pieceSelector().pawn, PieceSelector::Pawn::H);
    ASSERT_EQ(pawnHDescription.pieceSelectorType(), PieceType::Pawn);
}

// No longer possible to create invalid description
// TEST(PieceDescription, pawnInvalid){
//     using namespace Chess::Board;
//     auto pawnInvalidDescription = PieceDescription{SideSelector::Black, PieceSelector::Rook::H}; 
//     ASSERT_FALSE(pawnInvalidDescription.isValid());
//     ASSERT_EQ(pawnInvalidDescription.sideSelector(), SideSelector::Black);
//     ASSERT_EQ(pawnInvalidDescription.type(), PieceType::Pawn);
//     ASSERT_EQ(pawnInvalidDescription.pieceSelector().rook, PieceSelector::Rook::H);
//     ASSERT_EQ(pawnInvalidDescription.pieceSelectorType(), PieceType::Rook);
// }