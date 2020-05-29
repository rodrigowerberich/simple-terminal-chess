#include "gtest/gtest.h"
#include "Board/Board.hh"
#include "Board/BoardDefinitions.hh"

TEST(Board, moveOk){
    using namespace Chess::Board;
    Board board;    
    
    PieceDescription pieceDescription = Definitions::W_PB_DESCRIPTION;
    Position initialPosition = Definitions::pieceDefaultPosition(pieceDescription);
    Position newPosition = {Column::B, Row(3)};
    
    ASSERT_EQ(board.getPiecePosition(pieceDescription), initialPosition);
    ASSERT_EQ(board.getPieceAtPosition(initialPosition), pieceDescription);
    ASSERT_FALSE(board.getPieceAtPosition(newPosition).isValid());


    MoveResult moveResult = board.movePiece(pieceDescription, newPosition);

    ASSERT_EQ(moveResult.status(), MoveResult::Status::Ok);
    ASSERT_EQ(moveResult.info<MoveResult::Info::Ok>().oldPosition, initialPosition);
    ASSERT_EQ(moveResult.info<MoveResult::Info::Ok>().newPosition, newPosition);

    ASSERT_EQ(board.getPiecePosition(pieceDescription), newPosition);
    ASSERT_FALSE(board.getPieceAtPosition(initialPosition).isValid());
    ASSERT_EQ(board.getPieceAtPosition(newPosition), pieceDescription);
}

// TEST(Board, moveInvalidInputInvalidPieceSelector){
//     using namespace Chess::Board;
//     Board board;
    
//     PieceDescription pieceDescription = {SideSelector::White, PieceType::King, PieceSelector::Pawn::B};
//     Position newPosition = {Column::B, Row(3)};
//     MoveResult moveResult = board.movePiece(pieceDescription, newPosition);

//     ASSERT_EQ(moveResult.status(), MoveResult::Status::InvalidInput);
//     ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().type, MoveResult::Info::InvalidInput::Type::InvalidPieceSelector); 
//     ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.sideSelector(), SideSelector::White);
//     ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.type(), PieceType::King);
//     ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.pieceSelector().pawn, PieceSelector::Pawn::B);
//     ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.pieceSelectorType(), PieceType::Pawn);
// }

TEST(Board, moveInvalidInputInvalidPosition){
    using namespace Chess::Board;
    Board board;

    PieceDescription pieceDescription = Definitions::W_KE_DESCRIPTION;
    Position initialPosition = Definitions::pieceDefaultPosition(pieceDescription);    
    Position newPosition = {Column::B, Row(15)};
    MoveResult moveResult = board.movePiece(pieceDescription, newPosition);

    ASSERT_EQ(board.getPiecePosition(pieceDescription), initialPosition);
    ASSERT_EQ(board.getPieceAtPosition(initialPosition), pieceDescription);
    ASSERT_FALSE(board.getPieceAtPosition(newPosition).isValid());
    
    ASSERT_EQ(moveResult.status(), MoveResult::Status::InvalidInput);
    ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().type, MoveResult::Info::InvalidInput::Type::InvalidPosition); 
    ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.sideSelector(), SideSelector::White);
    ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.type(), PieceType::King);
    ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.pieceSelector().king, PieceSelector::King::E);
    ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.pieceSelectorType(), PieceType::King);
}

TEST(Board, moveCollisionDifferentSide){
    using namespace Chess::Board;
    Board board;    
    
    PieceDescription piece1Description = Definitions::W_PB_DESCRIPTION;
    Position piece1initialPosition = Definitions::pieceDefaultPosition(piece1Description);
    Position piece1newPosition = {Column::B, Row(3)};
    ASSERT_EQ(board.getPiecePosition(piece1Description), piece1initialPosition);
    MoveResult piece1moveResult = board.movePiece(piece1Description, piece1newPosition);
    ASSERT_EQ(piece1moveResult.status(), MoveResult::Status::Ok);
    ASSERT_EQ(piece1moveResult.info<MoveResult::Info::Ok>().oldPosition, piece1initialPosition);
    ASSERT_EQ(piece1moveResult.info<MoveResult::Info::Ok>().newPosition, piece1newPosition);
    ASSERT_EQ(board.getPiecePosition(piece1Description), piece1newPosition);

    PieceDescription piece2Description = Definitions::B_PB_DESCRIPTION;
    Position piece2initialPosition = Definitions::pieceDefaultPosition(piece2Description);
    Position piece2attemptedNewPosition = {Column::B, Row(3)};
    ASSERT_EQ(board.getPiecePosition(piece2Description), piece2initialPosition);
    MoveResult piece2moveResult = board.movePiece(piece2Description, piece2attemptedNewPosition);
    ASSERT_EQ(piece2moveResult.status(), MoveResult::Status::Collision);
    ASSERT_TRUE(piece2moveResult.info<MoveResult::Info::Collision>().differentSide);
    ASSERT_FALSE(piece2moveResult.info<MoveResult::Info::Collision>().sameSide);
    ASSERT_TRUE(piece2moveResult.info<MoveResult::Info::Collision>().originalPiece.isValid());
    ASSERT_EQ(piece2moveResult.info<MoveResult::Info::Collision>().originalPiece, piece2Description);
    ASSERT_TRUE(piece2moveResult.info<MoveResult::Info::Collision>().colidingPiece.isValid());
    ASSERT_EQ(piece2moveResult.info<MoveResult::Info::Collision>().colidingPiece, piece1Description);
    ASSERT_EQ(piece2moveResult.info<MoveResult::Info::Collision>().position, piece1newPosition);

    ASSERT_EQ(board.getPiecePosition(piece1Description), piece1newPosition);
    ASSERT_EQ(board.getPiecePosition(piece2Description), piece2initialPosition);
}

TEST(Board, moveCollisionSameSide){
    using namespace Chess::Board;
    Board board;    
    
    PieceDescription piece1Description = Definitions::W_PB_DESCRIPTION;
    Position piece1initialPosition = Definitions::pieceDefaultPosition(piece1Description);
    Position piece1newPosition = {Column::B, Row(3)};
    ASSERT_EQ(board.getPiecePosition(piece1Description), piece1initialPosition);
    MoveResult piece1moveResult = board.movePiece(piece1Description, piece1newPosition);
    ASSERT_EQ(piece1moveResult.status(), MoveResult::Status::Ok);
    ASSERT_EQ(piece1moveResult.info<MoveResult::Info::Ok>().oldPosition, piece1initialPosition);
    ASSERT_EQ(piece1moveResult.info<MoveResult::Info::Ok>().newPosition, piece1newPosition);
    ASSERT_EQ(board.getPiecePosition(piece1Description), piece1newPosition);

    PieceDescription piece2Description = Definitions::W_PC_DESCRIPTION;
    Position piece2initialPosition = Definitions::pieceDefaultPosition(piece2Description);
    Position piece2attemptedNewPosition = {Column::B, Row(3)};
    ASSERT_EQ(board.getPiecePosition(piece2Description), piece2initialPosition);
    MoveResult piece2moveResult = board.movePiece(piece2Description, piece2attemptedNewPosition);
    ASSERT_EQ(piece2moveResult.status(), MoveResult::Status::Collision);
    ASSERT_TRUE(piece2moveResult.info<MoveResult::Info::Collision>().sameSide);
    ASSERT_FALSE(piece2moveResult.info<MoveResult::Info::Collision>().differentSide);
    ASSERT_TRUE(piece2moveResult.info<MoveResult::Info::Collision>().originalPiece.isValid());
    ASSERT_EQ(piece2moveResult.info<MoveResult::Info::Collision>().originalPiece, piece2Description);
    ASSERT_TRUE(piece2moveResult.info<MoveResult::Info::Collision>().colidingPiece.isValid());
    ASSERT_EQ(piece2moveResult.info<MoveResult::Info::Collision>().colidingPiece, piece1Description);
    ASSERT_EQ(piece2moveResult.info<MoveResult::Info::Collision>().position, piece1newPosition);

    ASSERT_EQ(board.getPiecePosition(piece1Description), piece1newPosition);
    ASSERT_EQ(board.getPiecePosition(piece2Description), piece2initialPosition);
}

TEST(Board, noMovement){
    using namespace Chess::Board;
    Board board;    
    
    PieceDescription pieceDescription = Definitions::W_PB_DESCRIPTION;
    Position pieceinitialPosition = Definitions::pieceDefaultPosition(pieceDescription);
    Position pieceNewPosition = Definitions::pieceDefaultPosition(pieceDescription);
    ASSERT_EQ(pieceinitialPosition, pieceNewPosition);
    ASSERT_EQ(board.getPiecePosition(pieceDescription), pieceinitialPosition);
    ASSERT_EQ(board.getPieceAtPosition(pieceinitialPosition), pieceDescription);
    MoveResult pieceMoveResult = board.movePiece(pieceDescription, pieceNewPosition);

    ASSERT_EQ(pieceMoveResult.status(), MoveResult::Status::NoMovement);
    ASSERT_EQ(board.getPiecePosition(pieceDescription), pieceinitialPosition);
    ASSERT_EQ(board.getPieceAtPosition(pieceinitialPosition), pieceDescription);
}

TEST(Board, boardConstruction) {
    using namespace Chess::Board;
    Board board;

    Position W_PA = board.getPiecePosition(Definitions::W_PA_DESCRIPTION);
    Position W_PB = board.getPiecePosition(Definitions::W_PB_DESCRIPTION);
    Position W_PC = board.getPiecePosition(Definitions::W_PC_DESCRIPTION);
    Position W_PD = board.getPiecePosition(Definitions::W_PD_DESCRIPTION);
    Position W_PE = board.getPiecePosition(Definitions::W_PE_DESCRIPTION);
    Position W_PF = board.getPiecePosition(Definitions::W_PF_DESCRIPTION);
    Position W_PG = board.getPiecePosition(Definitions::W_PG_DESCRIPTION);
    Position W_PH = board.getPiecePosition(Definitions::W_PH_DESCRIPTION);
    Position W_RA = board.getPiecePosition(Definitions::W_RA_DESCRIPTION);
    Position W_kB = board.getPiecePosition(Definitions::W_kB_DESCRIPTION);
    Position W_BC = board.getPiecePosition(Definitions::W_BC_DESCRIPTION);
    Position W_Q  = board.getPiecePosition(Definitions::W_QD_DESCRIPTION);
    Position W_K  = board.getPiecePosition(Definitions::W_KE_DESCRIPTION);
    Position W_BF = board.getPiecePosition(Definitions::W_BF_DESCRIPTION);
    Position W_kG = board.getPiecePosition(Definitions::W_kG_DESCRIPTION);
    Position W_RH = board.getPiecePosition(Definitions::W_RH_DESCRIPTION);

    Position B_PA = board.getPiecePosition(Definitions::B_PA_DESCRIPTION);
    Position B_PB = board.getPiecePosition(Definitions::B_PB_DESCRIPTION);
    Position B_PC = board.getPiecePosition(Definitions::B_PC_DESCRIPTION);
    Position B_PD = board.getPiecePosition(Definitions::B_PD_DESCRIPTION);
    Position B_PE = board.getPiecePosition(Definitions::B_PE_DESCRIPTION);
    Position B_PF = board.getPiecePosition(Definitions::B_PF_DESCRIPTION);
    Position B_PG = board.getPiecePosition(Definitions::B_PG_DESCRIPTION);
    Position B_PH = board.getPiecePosition(Definitions::B_PH_DESCRIPTION);
    Position B_RA = board.getPiecePosition(Definitions::B_RA_DESCRIPTION);
    Position B_kB = board.getPiecePosition(Definitions::B_kB_DESCRIPTION);
    Position B_BC = board.getPiecePosition(Definitions::B_BC_DESCRIPTION);
    Position B_Q  = board.getPiecePosition(Definitions::B_QD_DESCRIPTION);
    Position B_K  = board.getPiecePosition(Definitions::B_KE_DESCRIPTION);
    Position B_BF = board.getPiecePosition(Definitions::B_BF_DESCRIPTION);
    Position B_kG = board.getPiecePosition(Definitions::B_kG_DESCRIPTION);
    Position B_RH = board.getPiecePosition(Definitions::B_RH_DESCRIPTION);


    ASSERT_EQ(Definitions::W_PA_POSITION,W_PA);
    ASSERT_EQ(Definitions::W_PB_POSITION,W_PB);
    ASSERT_EQ(Definitions::W_PC_POSITION,W_PC);
    ASSERT_EQ(Definitions::W_PD_POSITION,W_PD);
    ASSERT_EQ(Definitions::W_PE_POSITION,W_PE);
    ASSERT_EQ(Definitions::W_PF_POSITION,W_PF);
    ASSERT_EQ(Definitions::W_PG_POSITION,W_PG);
    ASSERT_EQ(Definitions::W_PH_POSITION,W_PH);
    ASSERT_EQ(Definitions::W_RA_POSITION,W_RA);
    ASSERT_EQ(Definitions::W_kB_POSITION,W_kB);
    ASSERT_EQ(Definitions::W_BC_POSITION,W_BC);
    ASSERT_EQ(Definitions::W_QD_POSITION ,W_Q );
    ASSERT_EQ(Definitions::W_KE_POSITION ,W_K );
    ASSERT_EQ(Definitions::W_BF_POSITION,W_BF);
    ASSERT_EQ(Definitions::W_kG_POSITION,W_kG);
    ASSERT_EQ(Definitions::W_RH_POSITION,W_RH);

    ASSERT_EQ(Definitions::B_PA_POSITION,B_PA);
    ASSERT_EQ(Definitions::B_PB_POSITION,B_PB);
    ASSERT_EQ(Definitions::B_PC_POSITION,B_PC);
    ASSERT_EQ(Definitions::B_PD_POSITION,B_PD);
    ASSERT_EQ(Definitions::B_PE_POSITION,B_PE);
    ASSERT_EQ(Definitions::B_PF_POSITION,B_PF);
    ASSERT_EQ(Definitions::B_PG_POSITION,B_PG);
    ASSERT_EQ(Definitions::B_PH_POSITION,B_PH);
    ASSERT_EQ(Definitions::B_RA_POSITION,B_RA);
    ASSERT_EQ(Definitions::B_kB_POSITION,B_kB);
    ASSERT_EQ(Definitions::B_BC_POSITION,B_BC);
    ASSERT_EQ(Definitions::B_QD_POSITION ,B_Q );
    ASSERT_EQ(Definitions::B_KE_POSITION ,B_K );
    ASSERT_EQ(Definitions::B_BF_POSITION,B_BF);
    ASSERT_EQ(Definitions::B_kG_POSITION,B_kG);
    ASSERT_EQ(Definitions::B_RH_POSITION,B_RH);


    auto A3Position = Position{Column::A, 3};
    auto B3Position = Position{Column::B, 3};
    auto C3Position = Position{Column::C, 3};
    auto D3Position = Position{Column::D, 3};
    auto E3Position = Position{Column::E, 3};
    auto F3Position = Position{Column::F, 3};
    auto G3Position = Position{Column::G, 3};
    auto H3Position = Position{Column::H, 3};
    auto A4Position = Position{Column::A, 4};
    auto B4Position = Position{Column::B, 4};
    auto C4Position = Position{Column::C, 4};
    auto D4Position = Position{Column::D, 4};
    auto E4Position = Position{Column::E, 4};
    auto F4Position = Position{Column::F, 4};
    auto G4Position = Position{Column::G, 4};
    auto H4Position = Position{Column::H, 4};
    auto A5Position = Position{Column::A, 5};
    auto B5Position = Position{Column::B, 5};
    auto C5Position = Position{Column::C, 5};
    auto D5Position = Position{Column::D, 5};
    auto E5Position = Position{Column::E, 5};
    auto F5Position = Position{Column::F, 5};
    auto G5Position = Position{Column::G, 5};
    auto H5Position = Position{Column::H, 5};
    auto A6Position = Position{Column::A, 6};
    auto B6Position = Position{Column::B, 6};
    auto C6Position = Position{Column::C, 6};
    auto D6Position = Position{Column::D, 6};
    auto E6Position = Position{Column::E, 6};
    auto F6Position = Position{Column::F, 6};
    auto G6Position = Position{Column::G, 6};
    auto H6Position = Position{Column::H, 6};

    
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_PA_POSITION), Definitions::W_PA_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_PB_POSITION), Definitions::W_PB_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_PC_POSITION), Definitions::W_PC_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_PD_POSITION), Definitions::W_PD_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_PE_POSITION), Definitions::W_PE_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_PF_POSITION), Definitions::W_PF_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_PG_POSITION), Definitions::W_PG_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_PH_POSITION), Definitions::W_PH_DESCRIPTION);
 
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_RA_POSITION), Definitions::W_RA_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_kB_POSITION), Definitions::W_kB_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_BC_POSITION), Definitions::W_BC_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_QD_POSITION), Definitions::W_QD_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_KE_POSITION), Definitions::W_KE_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_BF_POSITION), Definitions::W_BF_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_kG_POSITION), Definitions::W_kG_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::W_RH_POSITION), Definitions::W_RH_DESCRIPTION);

    ASSERT_FALSE(board.getPieceAtPosition(A3Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(B3Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(C3Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(D3Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(E3Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(F3Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(G3Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(H3Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(A4Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(B4Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(C4Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(D4Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(E4Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(F4Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(G4Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(H4Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(A5Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(B5Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(C5Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(D5Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(E5Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(F5Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(G5Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(H5Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(A6Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(B6Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(C6Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(D6Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(E6Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(F6Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(G6Position).isValid());
    ASSERT_FALSE(board.getPieceAtPosition(H6Position).isValid());

    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_PA_POSITION), Definitions::B_PA_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_PB_POSITION), Definitions::B_PB_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_PC_POSITION), Definitions::B_PC_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_PD_POSITION), Definitions::B_PD_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_PE_POSITION), Definitions::B_PE_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_PF_POSITION), Definitions::B_PF_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_PG_POSITION), Definitions::B_PG_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_PH_POSITION), Definitions::B_PH_DESCRIPTION);

    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_RA_POSITION), Definitions::B_RA_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_kB_POSITION), Definitions::B_kB_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_BC_POSITION), Definitions::B_BC_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_QD_POSITION), Definitions::B_QD_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_KE_POSITION), Definitions::B_KE_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_BF_POSITION), Definitions::B_BF_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_kG_POSITION), Definitions::B_kG_DESCRIPTION);
    ASSERT_EQ(board.getPieceAtPosition(Definitions::B_RH_POSITION), Definitions::B_RH_DESCRIPTION);
}