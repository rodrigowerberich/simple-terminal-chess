#include "gtest/gtest.h"
#include "Board/Side.hh"
#include "Board/Piece.hh"
#include "Board/BoardDefinitions.hh"

TEST(Side, whiteSideConstruction) {
    using namespace Chess;
    auto side = Board::Side(Board::SideSelector::White);

    auto& PA = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::A});
    auto& PB = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::B});
    auto& PC = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::C});
    auto& PD = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::D});
    auto& PE = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::E});
    auto& PF = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::F});
    auto& PG = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::G});
    auto& PH = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::H});
    auto& RA = side.getPiece(Board::PieceType::Rook,   {Board::PieceSelector::Rook::A});
    auto& kB = side.getPiece(Board::PieceType::Knight, {Board::PieceSelector::Knight::B});
    auto& BC = side.getPiece(Board::PieceType::Bishop, {Board::PieceSelector::Bishop::C});
    auto& Q = side.getPiece(Board::PieceType::Queen,   {Board::PieceSelector::Queen::D});
    auto& K = side.getPiece(Board::PieceType::King,    {Board::PieceSelector::King::E});
    auto& BF = side.getPiece(Board::PieceType::Bishop, {Board::PieceSelector::Bishop::F});
    auto& kG = side.getPiece(Board::PieceType::Knight, {Board::PieceSelector::Knight::G});
    auto& RH = side.getPiece(Board::PieceType::Rook,   {Board::PieceSelector::Rook::H});

    ASSERT_EQ(PA.currentPosition(), Board::Definitions::W_PA_POSITION);
    ASSERT_EQ(PB.currentPosition(), Board::Definitions::W_PB_POSITION);
    ASSERT_EQ(PC.currentPosition(), Board::Definitions::W_PC_POSITION);
    ASSERT_EQ(PD.currentPosition(), Board::Definitions::W_PD_POSITION);
    ASSERT_EQ(PE.currentPosition(), Board::Definitions::W_PE_POSITION);
    ASSERT_EQ(PF.currentPosition(), Board::Definitions::W_PF_POSITION);
    ASSERT_EQ(PG.currentPosition(), Board::Definitions::W_PG_POSITION);
    ASSERT_EQ(PH.currentPosition(), Board::Definitions::W_PH_POSITION);
    ASSERT_EQ(RA.currentPosition(), Board::Definitions::W_RA_POSITION);
    ASSERT_EQ(kB.currentPosition(), Board::Definitions::W_kB_POSITION);
    ASSERT_EQ(BC.currentPosition(), Board::Definitions::W_BC_POSITION);
    ASSERT_EQ(Q.currentPosition(),  Board::Definitions::W_QD_POSITION);
    ASSERT_EQ(K.currentPosition(),  Board::Definitions::W_KE_POSITION);
    ASSERT_EQ(BF.currentPosition(), Board::Definitions::W_BF_POSITION);
    ASSERT_EQ(kG.currentPosition(), Board::Definitions::W_kG_POSITION);
    ASSERT_EQ(RH.currentPosition(), Board::Definitions::W_RH_POSITION);
}

TEST(Side, blackSideConstruction) {
    using namespace Chess;
    auto side = Board::Side(Board::SideSelector::Black);

    auto& PA = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::A});
    auto& PB = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::B});
    auto& PC = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::C});
    auto& PD = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::D});
    auto& PE = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::E});
    auto& PF = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::F});
    auto& PG = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::G});
    auto& PH = side.getPiece(Board::PieceType::Pawn,   {Board::PieceSelector::Pawn::H});
    auto& RA = side.getPiece(Board::PieceType::Rook,   {Board::PieceSelector::Rook::A});
    auto& kB = side.getPiece(Board::PieceType::Knight, {Board::PieceSelector::Knight::B});
    auto& BC = side.getPiece(Board::PieceType::Bishop, {Board::PieceSelector::Bishop::C});
    auto& Q = side.getPiece(Board::PieceType::Queen,   {Board::PieceSelector::Queen::D});
    auto& K = side.getPiece(Board::PieceType::King,    {Board::PieceSelector::King::E});
    auto& BF = side.getPiece(Board::PieceType::Bishop, {Board::PieceSelector::Bishop::F});
    auto& kG = side.getPiece(Board::PieceType::Knight, {Board::PieceSelector::Knight::G});
    auto& RH = side.getPiece(Board::PieceType::Rook,   {Board::PieceSelector::Rook::H});

    ASSERT_EQ(PA.currentPosition(), Board::Definitions::B_PA_POSITION);
    ASSERT_EQ(PB.currentPosition(), Board::Definitions::B_PB_POSITION);
    ASSERT_EQ(PC.currentPosition(), Board::Definitions::B_PC_POSITION);
    ASSERT_EQ(PD.currentPosition(), Board::Definitions::B_PD_POSITION);
    ASSERT_EQ(PE.currentPosition(), Board::Definitions::B_PE_POSITION);
    ASSERT_EQ(PF.currentPosition(), Board::Definitions::B_PF_POSITION);
    ASSERT_EQ(PG.currentPosition(), Board::Definitions::B_PG_POSITION);
    ASSERT_EQ(PH.currentPosition(), Board::Definitions::B_PH_POSITION);
    ASSERT_EQ(RA.currentPosition(), Board::Definitions::B_RA_POSITION);
    ASSERT_EQ(kB.currentPosition(), Board::Definitions::B_kB_POSITION);
    ASSERT_EQ(BC.currentPosition(), Board::Definitions::B_BC_POSITION);
    ASSERT_EQ(Q.currentPosition(),  Board::Definitions::B_QD_POSITION);
    ASSERT_EQ(K.currentPosition(),  Board::Definitions::B_KE_POSITION);
    ASSERT_EQ(BF.currentPosition(), Board::Definitions::B_BF_POSITION);
    ASSERT_EQ(kG.currentPosition(), Board::Definitions::B_kG_POSITION);
    ASSERT_EQ(RH.currentPosition(), Board::Definitions::B_RH_POSITION);
}

TEST(Side, movePiece) {
    using namespace Chess;
    auto side = Board::Side(Board::SideSelector::Black);
    auto initialPosition = Board::Definitions::B_PA_POSITION;
    auto newPosition = Board::Position{Board::Column::A, 5};
    auto& pawnA = side.getPiece(Board::PieceType::Pawn, {Board::PieceSelector::Pawn::A});
    ASSERT_EQ(pawnA.currentPosition(), initialPosition);
    pawnA.setPosition(newPosition);
    ASSERT_EQ(pawnA.currentPosition(), newPosition);
    auto& newPawnARef = side.getPiece(Board::PieceType::Pawn, {Board::PieceSelector::Pawn::A});
    ASSERT_EQ(newPawnARef.currentPosition(), newPosition);
}

TEST(Side, invalidPiece){
    using namespace Chess;
    auto side = Board::Side(Board::SideSelector::Black);
    auto& invalidPiece = side.getPiece(Board::PieceType::King, {Board::PieceSelector::Pawn::H});
    ASSERT_FALSE(invalidPiece.currentPosition().isValid());
    ASSERT_FALSE(invalidPiece.isValid());
}