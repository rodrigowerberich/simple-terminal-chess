#include "gtest/gtest.h"
#include "Side.hh"
#include "Piece.hh"

TEST(Side, whiteSideConstruction) {
    using namespace Chess;
    auto side = Board::Side(Board::SideSelector::White);

    constexpr int frontRow = 2; 
    constexpr int backRow = 1; 

    auto correctPAPosition = Board::Position{Board::Column::A, frontRow};
    auto correctPBPosition = Board::Position{Board::Column::B, frontRow};
    auto correctPCPosition = Board::Position{Board::Column::C, frontRow};
    auto correctPDPosition = Board::Position{Board::Column::D, frontRow};
    auto correctPEPosition = Board::Position{Board::Column::E, frontRow};
    auto correctPFPosition = Board::Position{Board::Column::F, frontRow};
    auto correctPGPosition = Board::Position{Board::Column::G, frontRow};
    auto correctPHPosition = Board::Position{Board::Column::H, frontRow};

    auto correctRAPosition = Board::Position{Board::Column::A,backRow};
    auto correctkBPosition = Board::Position{Board::Column::B,backRow};
    auto correctBCPosition = Board::Position{Board::Column::C,backRow};
    auto correctKPosition  = Board::Position{Board::Column::D,backRow};
    auto correctQPosition  = Board::Position{Board::Column::E,backRow};
    auto correctBFPosition = Board::Position{Board::Column::F,backRow};
    auto correctkGPosition = Board::Position{Board::Column::G,backRow};
    auto correctRHPosition = Board::Position{Board::Column::H,backRow};

    
    auto& PA = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::A});
    ASSERT_EQ(PA.currentPosition(), correctPAPosition);
    auto& PB = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::B});
    ASSERT_EQ(PB.currentPosition(), correctPBPosition);
    auto& PC = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::C});
    ASSERT_EQ(PC.currentPosition(), correctPCPosition);
    auto& PD = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::D});
    ASSERT_EQ(PD.currentPosition(), correctPDPosition);
    auto& PE = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::E});
    ASSERT_EQ(PE.currentPosition(), correctPEPosition);
    auto& PF = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::F});
    ASSERT_EQ(PF.currentPosition(), correctPFPosition);
    auto& PG = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::G});
    ASSERT_EQ(PG.currentPosition(), correctPGPosition);
    auto& PH = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::H});
    ASSERT_EQ(PH.currentPosition(), correctPHPosition);

    auto& RA = side.getPiece(Board::PieceType::Rook,  {Board::PieceSelector::Rook::A});
    ASSERT_EQ(RA.currentPosition(), correctRAPosition);
    auto& RH = side.getPiece(Board::PieceType::Rook,  {Board::PieceSelector::Rook::H});
    ASSERT_EQ(RH.currentPosition(), correctRHPosition);

    auto& kB = side.getPiece(Board::PieceType::Knight,  {Board::PieceSelector::Knight::B});
    ASSERT_EQ(kB.currentPosition(), correctkBPosition);
    auto& kG = side.getPiece(Board::PieceType::Knight,  {Board::PieceSelector::Knight::G});
    ASSERT_EQ(kG.currentPosition(), correctkGPosition);

    auto& BC = side.getPiece(Board::PieceType::Bishop,  {Board::PieceSelector::Bishop::C});
    ASSERT_EQ(BC.currentPosition(), correctBCPosition);
    auto& BF = side.getPiece(Board::PieceType::Bishop,  {Board::PieceSelector::Bishop::F});
    ASSERT_EQ(BF.currentPosition(), correctBFPosition);

    auto& Q = side.getPiece(Board::PieceType::Queen,  {Board::PieceSelector::Queen::E});
    ASSERT_EQ(Q.currentPosition(), correctQPosition);

    auto& K = side.getPiece(Board::PieceType::King,  {Board::PieceSelector::King::D});
    ASSERT_EQ(K.currentPosition(), correctKPosition);
}

TEST(Side, blackSideConstruction) {
    using namespace Chess;
    auto side = Board::Side(Board::SideSelector::Black);

    constexpr int frontRow = 7; 
    constexpr int backRow = 8; 

    auto correctPAPosition = Board::Position{Board::Column::A, frontRow};
    auto correctPBPosition = Board::Position{Board::Column::B, frontRow};
    auto correctPCPosition = Board::Position{Board::Column::C, frontRow};
    auto correctPDPosition = Board::Position{Board::Column::D, frontRow};
    auto correctPEPosition = Board::Position{Board::Column::E, frontRow};
    auto correctPFPosition = Board::Position{Board::Column::F, frontRow};
    auto correctPGPosition = Board::Position{Board::Column::G, frontRow};
    auto correctPHPosition = Board::Position{Board::Column::H, frontRow};

    auto correctRAPosition = Board::Position{Board::Column::A,backRow};
    auto correctkBPosition = Board::Position{Board::Column::B,backRow};
    auto correctBCPosition = Board::Position{Board::Column::C,backRow};
    auto correctKPosition  = Board::Position{Board::Column::D,backRow};
    auto correctQPosition  = Board::Position{Board::Column::E,backRow};
    auto correctBFPosition = Board::Position{Board::Column::F,backRow};
    auto correctkGPosition = Board::Position{Board::Column::G,backRow};
    auto correctRHPosition = Board::Position{Board::Column::H,backRow};

    
    auto& PA = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::A});
    ASSERT_EQ(PA.currentPosition(), correctPAPosition);
    auto& PB = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::B});
    ASSERT_EQ(PB.currentPosition(), correctPBPosition);
    auto& PC = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::C});
    ASSERT_EQ(PC.currentPosition(), correctPCPosition);
    auto& PD = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::D});
    ASSERT_EQ(PD.currentPosition(), correctPDPosition);
    auto& PE = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::E});
    ASSERT_EQ(PE.currentPosition(), correctPEPosition);
    auto& PF = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::F});
    ASSERT_EQ(PF.currentPosition(), correctPFPosition);
    auto& PG = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::G});
    ASSERT_EQ(PG.currentPosition(), correctPGPosition);
    auto& PH = side.getPiece(Board::PieceType::Pawn,  {Board::PieceSelector::Pawn::H});
    ASSERT_EQ(PH.currentPosition(), correctPHPosition);

    auto& RA = side.getPiece(Board::PieceType::Rook,  {Board::PieceSelector::Rook::A});
    ASSERT_EQ(RA.currentPosition(), correctRAPosition);
    auto& RH = side.getPiece(Board::PieceType::Rook,  {Board::PieceSelector::Rook::H});
    ASSERT_EQ(RH.currentPosition(), correctRHPosition);

    auto& kB = side.getPiece(Board::PieceType::Knight,  {Board::PieceSelector::Knight::B});
    ASSERT_EQ(kB.currentPosition(), correctkBPosition);
    auto& kG = side.getPiece(Board::PieceType::Knight,  {Board::PieceSelector::Knight::G});
    ASSERT_EQ(kG.currentPosition(), correctkGPosition);

    auto& BC = side.getPiece(Board::PieceType::Bishop,  {Board::PieceSelector::Bishop::C});
    ASSERT_EQ(BC.currentPosition(), correctBCPosition);
    auto& BF = side.getPiece(Board::PieceType::Bishop,  {Board::PieceSelector::Bishop::F});
    ASSERT_EQ(BF.currentPosition(), correctBFPosition);

    auto& Q = side.getPiece(Board::PieceType::Queen,  {Board::PieceSelector::Queen::E});
    ASSERT_EQ(Q.currentPosition(), correctQPosition);

    auto& K = side.getPiece(Board::PieceType::King,  {Board::PieceSelector::King::D});
    ASSERT_EQ(K.currentPosition(), correctKPosition);
}

TEST(Side, movePiece) {
    using namespace Chess;
    auto side = Board::Side(Board::SideSelector::Black);
    auto initialPosition = Board::Position{Board::Column::A, 7};
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