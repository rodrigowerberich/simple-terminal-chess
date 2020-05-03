#include "gtest/gtest.h"
#include "Board.hh"

TEST(Board, moveOk){
    using namespace Chess::Board;
    Board board;    
    
    PieceDescription pieceDescription = {SideSelector::White, PieceType::Pawn, PieceSelector::Pawn::B};
    Position initialPosition = {Column::B, Row(2)};
    Position newPosition = {Column::B, Row(3)};
    
    ASSERT_EQ(board.getPiecePosition(pieceDescription), initialPosition);

    MoveResult moveResult = board.movePiece(pieceDescription, newPosition);

    ASSERT_EQ(moveResult.status(), MoveResult::Status::Ok);
    ASSERT_EQ(moveResult.info<MoveResult::Info::Ok>().oldPosition, initialPosition);
    ASSERT_EQ(moveResult.info<MoveResult::Info::Ok>().newPosition, newPosition);

    ASSERT_EQ(board.getPiecePosition(pieceDescription), newPosition);
}

TEST(Board, moveInvalidInputInvalidPieceSelector){
    using namespace Chess::Board;
    Board board;
    
    PieceDescription pieceDescription = {SideSelector::White, PieceType::King, PieceSelector::Pawn::B};
    Position newPosition = {Column::B, Row(3)};
    MoveResult moveResult = board.movePiece(pieceDescription, newPosition);
    ASSERT_EQ(moveResult.status(), MoveResult::Status::InvalidInput);
    ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().type, MoveResult::Info::InvalidInput::Type::InvalidPieceSelector); 
    ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.sideSelector(), SideSelector::White);
    ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.type(), PieceType::King);
    ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.pieceSelector().pawn, PieceSelector::Pawn::B);
    ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.pieceSelectorType(), PieceType::Pawn);
}

TEST(Board, moveInvalidInputInvalidPosition){
    using namespace Chess::Board;
    Board board;
    
    PieceDescription pieceDescription = {SideSelector::White, PieceType::King, PieceSelector::King::D};
    Position newPosition = {Column::B, Row(15)};
    MoveResult moveResult = board.movePiece(pieceDescription, newPosition);
    ASSERT_EQ(moveResult.status(), MoveResult::Status::InvalidInput);
    ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().type, MoveResult::Info::InvalidInput::Type::InvalidPosition); 
    ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.sideSelector(), SideSelector::White);
    ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.type(), PieceType::King);
    ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.pieceSelector().king, PieceSelector::King::D);
    ASSERT_EQ(moveResult.info<MoveResult::Info::InvalidInput>().invalidPieceDescription.pieceSelectorType(), PieceType::King);
}


TEST(Board, boardConstruction) {
    using namespace Chess;
    Board::Board board;

    constexpr int whiteFrontRow = 2; 
    constexpr int whiteBackRow = 1; 
    constexpr int blackFrontRow = 7; 
    constexpr int blackBackRow = 8; 


    auto correctWhitePAPosition = Board::Position{Board::Column::A, whiteFrontRow};
    auto correctWhitePBPosition = Board::Position{Board::Column::B, whiteFrontRow};
    auto correctWhitePCPosition = Board::Position{Board::Column::C, whiteFrontRow};
    auto correctWhitePDPosition = Board::Position{Board::Column::D, whiteFrontRow};
    auto correctWhitePEPosition = Board::Position{Board::Column::E, whiteFrontRow};
    auto correctWhitePFPosition = Board::Position{Board::Column::F, whiteFrontRow};
    auto correctWhitePGPosition = Board::Position{Board::Column::G, whiteFrontRow};
    auto correctWhitePHPosition = Board::Position{Board::Column::H, whiteFrontRow};
    auto correctWhiteRAPosition = Board::Position{Board::Column::A, whiteBackRow};
    auto correctWhitekBPosition = Board::Position{Board::Column::B, whiteBackRow};
    auto correctWhiteBCPosition = Board::Position{Board::Column::C, whiteBackRow};
    auto correctWhiteKPosition  = Board::Position{Board::Column::D, whiteBackRow};
    auto correctWhiteQPosition  = Board::Position{Board::Column::E, whiteBackRow};
    auto correctWhiteBFPosition = Board::Position{Board::Column::F, whiteBackRow};
    auto correctWhitekGPosition = Board::Position{Board::Column::G, whiteBackRow};
    auto correctWhiteRHPosition = Board::Position{Board::Column::H, whiteBackRow};

    auto correctBlackPAPosition = Board::Position{Board::Column::A, blackFrontRow};
    auto correctBlackPBPosition = Board::Position{Board::Column::B, blackFrontRow};
    auto correctBlackPCPosition = Board::Position{Board::Column::C, blackFrontRow};
    auto correctBlackPDPosition = Board::Position{Board::Column::D, blackFrontRow};
    auto correctBlackPEPosition = Board::Position{Board::Column::E, blackFrontRow};
    auto correctBlackPFPosition = Board::Position{Board::Column::F, blackFrontRow};
    auto correctBlackPGPosition = Board::Position{Board::Column::G, blackFrontRow};
    auto correctBlackPHPosition = Board::Position{Board::Column::H, blackFrontRow};
    auto correctBlackRAPosition = Board::Position{Board::Column::A, blackBackRow};
    auto correctBlackkBPosition = Board::Position{Board::Column::B, blackBackRow};
    auto correctBlackBCPosition = Board::Position{Board::Column::C, blackBackRow};
    auto correctBlackKPosition  = Board::Position{Board::Column::D, blackBackRow};
    auto correctBlackQPosition  = Board::Position{Board::Column::E, blackBackRow};
    auto correctBlackBFPosition = Board::Position{Board::Column::F, blackBackRow};
    auto correctBlackkGPosition = Board::Position{Board::Column::G, blackBackRow};
    auto correctBlackRHPosition = Board::Position{Board::Column::H, blackBackRow};

    Board::Position W_PA = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::A});
    Board::Position W_PB = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::B});
    Board::Position W_PC = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::C});
    Board::Position W_PD = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::D});
    Board::Position W_PE = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::E});
    Board::Position W_PF = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::F});
    Board::Position W_PG = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::G});
    Board::Position W_PH = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::H});
    Board::Position W_RA = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::Rook, Board::PieceSelector::Rook::A});
    Board::Position W_kB = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::Knight, Board::PieceSelector::Knight::B});
    Board::Position W_BC = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::Bishop, Board::PieceSelector::Bishop::C});
    Board::Position W_K  = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::King, Board::PieceSelector::King::D});
    Board::Position W_Q  = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::Queen, Board::PieceSelector::Queen::E});
    Board::Position W_BF = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::Bishop, Board::PieceSelector::Bishop::F});
    Board::Position W_kG = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::Knight, Board::PieceSelector::Knight::G});
    Board::Position W_RH = board.getPiecePosition({Board::SideSelector::White, Board::PieceType::Rook, Board::PieceSelector::Rook::H});

    Board::Position B_PA = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::A});
    Board::Position B_PB = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::B});
    Board::Position B_PC = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::C});
    Board::Position B_PD = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::D});
    Board::Position B_PE = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::E});
    Board::Position B_PF = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::F});
    Board::Position B_PG = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::G});
    Board::Position B_PH = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::H});
    Board::Position B_RA = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::Rook, Board::PieceSelector::Rook::A});
    Board::Position B_kB = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::Knight, Board::PieceSelector::Knight::B});
    Board::Position B_BC = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::Bishop, Board::PieceSelector::Bishop::C});
    Board::Position B_K  = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::King, Board::PieceSelector::King::D});
    Board::Position B_Q  = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::Queen, Board::PieceSelector::Queen::E});
    Board::Position B_BF = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::Bishop, Board::PieceSelector::Bishop::F});
    Board::Position B_kG = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::Knight, Board::PieceSelector::Knight::G});
    Board::Position B_RH = board.getPiecePosition({Board::SideSelector::Black, Board::PieceType::Rook, Board::PieceSelector::Rook::H});

    ASSERT_EQ(correctWhitePAPosition,W_PA);
    ASSERT_EQ(correctWhitePBPosition,W_PB);
    ASSERT_EQ(correctWhitePCPosition,W_PC);
    ASSERT_EQ(correctWhitePDPosition,W_PD);
    ASSERT_EQ(correctWhitePEPosition,W_PE);
    ASSERT_EQ(correctWhitePFPosition,W_PF);
    ASSERT_EQ(correctWhitePGPosition,W_PG);
    ASSERT_EQ(correctWhitePHPosition,W_PH);
    ASSERT_EQ(correctWhiteRAPosition,W_RA);
    ASSERT_EQ(correctWhitekBPosition,W_kB);
    ASSERT_EQ(correctWhiteBCPosition,W_BC);
    ASSERT_EQ(correctWhiteKPosition ,W_K );
    ASSERT_EQ(correctWhiteQPosition ,W_Q );
    ASSERT_EQ(correctWhiteBFPosition,W_BF);
    ASSERT_EQ(correctWhitekGPosition,W_kG);
    ASSERT_EQ(correctWhiteRHPosition,W_RH);

    ASSERT_EQ(correctBlackPAPosition,B_PA);
    ASSERT_EQ(correctBlackPBPosition,B_PB);
    ASSERT_EQ(correctBlackPCPosition,B_PC);
    ASSERT_EQ(correctBlackPDPosition,B_PD);
    ASSERT_EQ(correctBlackPEPosition,B_PE);
    ASSERT_EQ(correctBlackPFPosition,B_PF);
    ASSERT_EQ(correctBlackPGPosition,B_PG);
    ASSERT_EQ(correctBlackPHPosition,B_PH);
    ASSERT_EQ(correctBlackRAPosition,B_RA);
    ASSERT_EQ(correctBlackkBPosition,B_kB);
    ASSERT_EQ(correctBlackBCPosition,B_BC);
    ASSERT_EQ(correctBlackKPosition ,B_K );
    ASSERT_EQ(correctBlackQPosition ,B_Q );
    ASSERT_EQ(correctBlackBFPosition,B_BF);
    ASSERT_EQ(correctBlackkGPosition,B_kG);
    ASSERT_EQ(correctBlackRHPosition,B_RH);
    

}