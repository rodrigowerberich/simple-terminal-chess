#include "gtest/gtest.h"
#include "Board.hh"

TEST(Board, moveOk){
    using namespace Chess::Board;
    Board board;    
    
    PieceDescription pieceDescription = {SideSelector::White, PieceType::Pawn, PieceSelector::Pawn::B};
    Position initialPosition = {Column::B, Row(2)};
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

    Position initialPosition = {Column::E, Row(1)};    
    PieceDescription pieceDescription = {SideSelector::White, PieceType::King, PieceSelector::King::E};
    Position newPosition = {Column::B, Row(15)};
    MoveResult moveResult = board.movePiece(pieceDescription, newPosition);

    std::cout << board.getPiecePosition(pieceDescription) << std::endl;
    std::cout << initialPosition << std::endl;
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
    
    PieceDescription piece1Description = {SideSelector::White, PieceType::Pawn, PieceSelector::Pawn::B};
    Position piece1initialPosition = {Column::B, Row(2)};
    Position piece1newPosition = {Column::B, Row(3)};
    ASSERT_EQ(board.getPiecePosition(piece1Description), piece1initialPosition);
    MoveResult piece1moveResult = board.movePiece(piece1Description, piece1newPosition);
    ASSERT_EQ(piece1moveResult.status(), MoveResult::Status::Ok);
    ASSERT_EQ(piece1moveResult.info<MoveResult::Info::Ok>().oldPosition, piece1initialPosition);
    ASSERT_EQ(piece1moveResult.info<MoveResult::Info::Ok>().newPosition, piece1newPosition);
    ASSERT_EQ(board.getPiecePosition(piece1Description), piece1newPosition);

    PieceDescription piece2Description = {SideSelector::Black, PieceType::Pawn, PieceSelector::Pawn::B};
    Position piece2initialPosition = {Column::B, Row(7)};
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
    
    PieceDescription piece1Description = {SideSelector::White, PieceType::Pawn, PieceSelector::Pawn::B};
    Position piece1initialPosition = {Column::B, Row(2)};
    Position piece1newPosition = {Column::B, Row(3)};
    ASSERT_EQ(board.getPiecePosition(piece1Description), piece1initialPosition);
    MoveResult piece1moveResult = board.movePiece(piece1Description, piece1newPosition);
    ASSERT_EQ(piece1moveResult.status(), MoveResult::Status::Ok);
    ASSERT_EQ(piece1moveResult.info<MoveResult::Info::Ok>().oldPosition, piece1initialPosition);
    ASSERT_EQ(piece1moveResult.info<MoveResult::Info::Ok>().newPosition, piece1newPosition);
    ASSERT_EQ(board.getPiecePosition(piece1Description), piece1newPosition);

    PieceDescription piece2Description = {SideSelector::White, PieceType::Pawn, PieceSelector::Pawn::C};
    Position piece2initialPosition = {Column::C, Row(2)};
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
    
    PieceDescription pieceDescription = {SideSelector::White, PieceType::Pawn, PieceSelector::Pawn::B};
    Position pieceinitialPosition = {Column::B, Row(2)};
    Position pieceNewPosition = {Column::B, Row(2)};
    ASSERT_EQ(pieceinitialPosition, pieceNewPosition);
    ASSERT_EQ(board.getPiecePosition(pieceDescription), pieceinitialPosition);
    ASSERT_EQ(board.getPieceAtPosition(pieceinitialPosition), pieceDescription);
    MoveResult pieceMoveResult = board.movePiece(pieceDescription, pieceNewPosition);

    ASSERT_EQ(pieceMoveResult.status(), MoveResult::Status::NoMovement);
    ASSERT_EQ(board.getPiecePosition(pieceDescription), pieceinitialPosition);
    ASSERT_EQ(board.getPieceAtPosition(pieceinitialPosition), pieceDescription);
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
    auto correctWhiteQPosition  = Board::Position{Board::Column::D, whiteBackRow};
    auto correctWhiteKPosition  = Board::Position{Board::Column::E, whiteBackRow};
    auto correctWhiteBFPosition = Board::Position{Board::Column::F, whiteBackRow};
    auto correctWhitekGPosition = Board::Position{Board::Column::G, whiteBackRow};
    auto correctWhiteRHPosition = Board::Position{Board::Column::H, whiteBackRow};

    auto whitePADescription = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::A};
    auto whitePBDescription = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::B};
    auto whitePCDescription = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::C};
    auto whitePDDescription = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::D};
    auto whitePEDescription = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::E};
    auto whitePFDescription = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::F};
    auto whitePGDescription = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::G};
    auto whitePHDescription = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::Pawn, Board::PieceSelector::Pawn::H};
    auto whiteRADescription = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::Rook, Board::PieceSelector::Rook::A};
    auto whitekBDescription = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::Knight, Board::PieceSelector::Knight::B};
    auto whiteBCDescription = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::Bishop, Board::PieceSelector::Bishop::C};
    auto whiteQDescription  = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::Queen, Board::PieceSelector::Queen::D};
    auto whiteKDescription  = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::King, Board::PieceSelector::King::E};
    auto whiteBFDescription = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::Bishop, Board::PieceSelector::Bishop::F};
    auto whitekGDescription = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::Knight, Board::PieceSelector::Knight::G};
    auto whiteRHDescription = Board::PieceDescription{Board::SideSelector::White, Board::PieceType::Rook, Board::PieceSelector::Rook::H};

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
    auto correctBlackQPosition  = Board::Position{Board::Column::D, blackBackRow};
    auto correctBlackKPosition  = Board::Position{Board::Column::E, blackBackRow};
    auto correctBlackBFPosition = Board::Position{Board::Column::F, blackBackRow};
    auto correctBlackkGPosition = Board::Position{Board::Column::G, blackBackRow};
    auto correctBlackRHPosition = Board::Position{Board::Column::H, blackBackRow};

    auto blackPADescription = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::A};
    auto blackPBDescription = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::B};
    auto blackPCDescription = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::C};
    auto blackPDDescription = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::D};
    auto blackPEDescription = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::E};
    auto blackPFDescription = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::F};
    auto blackPGDescription = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::G};
    auto blackPHDescription = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::Pawn, Board::PieceSelector::Pawn::H};
    auto blackRADescription = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::Rook, Board::PieceSelector::Rook::A};
    auto blackkBDescription = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::Knight, Board::PieceSelector::Knight::B};
    auto blackBCDescription = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::Bishop, Board::PieceSelector::Bishop::C};
    auto blackQDescription  = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::Queen, Board::PieceSelector::Queen::D};
    auto blackKDescription  = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::King, Board::PieceSelector::King::E};
    auto blackBFDescription = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::Bishop, Board::PieceSelector::Bishop::F};
    auto blackkGDescription = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::Knight, Board::PieceSelector::Knight::G};
    auto blackRHDescription = Board::PieceDescription{Board::SideSelector::Black, Board::PieceType::Rook, Board::PieceSelector::Rook::H};


    Board::Position W_PA = board.getPiecePosition(whitePADescription);
    Board::Position W_PB = board.getPiecePosition(whitePBDescription);
    Board::Position W_PC = board.getPiecePosition(whitePCDescription);
    Board::Position W_PD = board.getPiecePosition(whitePDDescription);
    Board::Position W_PE = board.getPiecePosition(whitePEDescription);
    Board::Position W_PF = board.getPiecePosition(whitePFDescription);
    Board::Position W_PG = board.getPiecePosition(whitePGDescription);
    Board::Position W_PH = board.getPiecePosition(whitePHDescription);
    Board::Position W_RA = board.getPiecePosition(whiteRADescription);
    Board::Position W_kB = board.getPiecePosition(whitekBDescription);
    Board::Position W_BC = board.getPiecePosition(whiteBCDescription);
    Board::Position W_K  = board.getPiecePosition(whiteKDescription );
    Board::Position W_Q  = board.getPiecePosition(whiteQDescription );
    Board::Position W_BF = board.getPiecePosition(whiteBFDescription);
    Board::Position W_kG = board.getPiecePosition(whitekGDescription);
    Board::Position W_RH = board.getPiecePosition(whiteRHDescription);

    Board::Position B_PA = board.getPiecePosition(blackPADescription);
    Board::Position B_PB = board.getPiecePosition(blackPBDescription);
    Board::Position B_PC = board.getPiecePosition(blackPCDescription);
    Board::Position B_PD = board.getPiecePosition(blackPDDescription);
    Board::Position B_PE = board.getPiecePosition(blackPEDescription);
    Board::Position B_PF = board.getPiecePosition(blackPFDescription);
    Board::Position B_PG = board.getPiecePosition(blackPGDescription);
    Board::Position B_PH = board.getPiecePosition(blackPHDescription);
    Board::Position B_RA = board.getPiecePosition(blackRADescription);
    Board::Position B_kB = board.getPiecePosition(blackkBDescription);
    Board::Position B_BC = board.getPiecePosition(blackBCDescription);
    Board::Position B_K  = board.getPiecePosition(blackKDescription );
    Board::Position B_Q  = board.getPiecePosition(blackQDescription );
    Board::Position B_BF = board.getPiecePosition(blackBFDescription);
    Board::Position B_kG = board.getPiecePosition(blackkGDescription);
    Board::Position B_RH = board.getPiecePosition(blackRHDescription);

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


    auto A3Position = Board::Position{Board::Column::A, 3};
    auto B3Position = Board::Position{Board::Column::B, 3};
    auto C3Position = Board::Position{Board::Column::C, 3};
    auto D3Position = Board::Position{Board::Column::D, 3};
    auto E3Position = Board::Position{Board::Column::E, 3};
    auto F3Position = Board::Position{Board::Column::F, 3};
    auto G3Position = Board::Position{Board::Column::G, 3};
    auto H3Position = Board::Position{Board::Column::H, 3};
    auto A4Position = Board::Position{Board::Column::A, 4};
    auto B4Position = Board::Position{Board::Column::B, 4};
    auto C4Position = Board::Position{Board::Column::C, 4};
    auto D4Position = Board::Position{Board::Column::D, 4};
    auto E4Position = Board::Position{Board::Column::E, 4};
    auto F4Position = Board::Position{Board::Column::F, 4};
    auto G4Position = Board::Position{Board::Column::G, 4};
    auto H4Position = Board::Position{Board::Column::H, 4};
    auto A5Position = Board::Position{Board::Column::A, 5};
    auto B5Position = Board::Position{Board::Column::B, 5};
    auto C5Position = Board::Position{Board::Column::C, 5};
    auto D5Position = Board::Position{Board::Column::D, 5};
    auto E5Position = Board::Position{Board::Column::E, 5};
    auto F5Position = Board::Position{Board::Column::F, 5};
    auto G5Position = Board::Position{Board::Column::G, 5};
    auto H5Position = Board::Position{Board::Column::H, 5};
    auto A6Position = Board::Position{Board::Column::A, 6};
    auto B6Position = Board::Position{Board::Column::B, 6};
    auto C6Position = Board::Position{Board::Column::C, 6};
    auto D6Position = Board::Position{Board::Column::D, 6};
    auto E6Position = Board::Position{Board::Column::E, 6};
    auto F6Position = Board::Position{Board::Column::F, 6};
    auto G6Position = Board::Position{Board::Column::G, 6};
    auto H6Position = Board::Position{Board::Column::H, 6};

    
    ASSERT_EQ(board.getPieceAtPosition(correctWhitePAPosition), whitePADescription);
    ASSERT_EQ(board.getPieceAtPosition(correctWhitePBPosition), whitePBDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctWhitePCPosition), whitePCDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctWhitePDPosition), whitePDDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctWhitePEPosition), whitePEDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctWhitePFPosition), whitePFDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctWhitePGPosition), whitePGDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctWhitePHPosition), whitePHDescription);
 
    ASSERT_EQ(board.getPieceAtPosition(correctWhiteRAPosition), whiteRADescription);
    ASSERT_EQ(board.getPieceAtPosition(correctWhitekBPosition), whitekBDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctWhiteBCPosition), whiteBCDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctWhiteKPosition) , whiteKDescription );
    ASSERT_EQ(board.getPieceAtPosition(correctWhiteQPosition) , whiteQDescription );
    ASSERT_EQ(board.getPieceAtPosition(correctWhiteBFPosition), whiteBFDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctWhitekGPosition), whitekGDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctWhiteRHPosition), whiteRHDescription);

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

    ASSERT_EQ(board.getPieceAtPosition(correctBlackPAPosition), blackPADescription);
    ASSERT_EQ(board.getPieceAtPosition(correctBlackPBPosition), blackPBDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctBlackPCPosition), blackPCDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctBlackPDPosition), blackPDDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctBlackPEPosition), blackPEDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctBlackPFPosition), blackPFDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctBlackPGPosition), blackPGDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctBlackPHPosition), blackPHDescription);

    ASSERT_EQ(board.getPieceAtPosition(correctBlackRAPosition), blackRADescription);
    ASSERT_EQ(board.getPieceAtPosition(correctBlackkBPosition), blackkBDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctBlackBCPosition), blackBCDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctBlackKPosition) , blackKDescription );
    ASSERT_EQ(board.getPieceAtPosition(correctBlackQPosition) , blackQDescription );
    ASSERT_EQ(board.getPieceAtPosition(correctBlackBFPosition), blackBFDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctBlackkGPosition), blackkGDescription);
    ASSERT_EQ(board.getPieceAtPosition(correctBlackRHPosition), blackRHDescription);
}