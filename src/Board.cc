#include "Board.hh"

namespace Chess{
namespace Board{

Board::Board():
m_whiteSide{Chess::Board::SideSelector::White},
m_blackSide{Chess::Board::SideSelector::Black}{
    m_occupancyMap[Chess::Board::Column::A][Chess::Board::Row(1)] = {SideSelector::White, PieceType::Rook, PieceSelector::Rook::A};
    m_occupancyMap[Chess::Board::Column::B][Chess::Board::Row(1)] = {SideSelector::White, PieceType::Knight, PieceSelector::Knight::B};
    m_occupancyMap[Chess::Board::Column::C][Chess::Board::Row(1)] = {SideSelector::White, PieceType::Bishop, PieceSelector::Bishop::C};
    m_occupancyMap[Chess::Board::Column::D][Chess::Board::Row(1)] = {SideSelector::White, PieceType::King, PieceSelector::King::D};
    m_occupancyMap[Chess::Board::Column::E][Chess::Board::Row(1)] = {SideSelector::White, PieceType::Queen, PieceSelector::Queen::E};
    m_occupancyMap[Chess::Board::Column::F][Chess::Board::Row(1)] = {SideSelector::White, PieceType::Bishop, PieceSelector::Bishop::F};
    m_occupancyMap[Chess::Board::Column::G][Chess::Board::Row(1)] = {SideSelector::White, PieceType::Knight, PieceSelector::Knight::G};
    m_occupancyMap[Chess::Board::Column::H][Chess::Board::Row(1)] = {SideSelector::White, PieceType::Rook, PieceSelector::Rook::H};

    m_occupancyMap[Chess::Board::Column::A][Chess::Board::Row(2)] = {SideSelector::White, PieceType::Pawn, PieceSelector::Pawn::A};
    m_occupancyMap[Chess::Board::Column::B][Chess::Board::Row(2)] = {SideSelector::White, PieceType::Pawn, PieceSelector::Pawn::B};
    m_occupancyMap[Chess::Board::Column::C][Chess::Board::Row(2)] = {SideSelector::White, PieceType::Pawn, PieceSelector::Pawn::C};
    m_occupancyMap[Chess::Board::Column::D][Chess::Board::Row(2)] = {SideSelector::White, PieceType::Pawn, PieceSelector::Pawn::D};
    m_occupancyMap[Chess::Board::Column::E][Chess::Board::Row(2)] = {SideSelector::White, PieceType::Pawn, PieceSelector::Pawn::E};
    m_occupancyMap[Chess::Board::Column::F][Chess::Board::Row(2)] = {SideSelector::White, PieceType::Pawn, PieceSelector::Pawn::F};
    m_occupancyMap[Chess::Board::Column::G][Chess::Board::Row(2)] = {SideSelector::White, PieceType::Pawn, PieceSelector::Pawn::G};
    m_occupancyMap[Chess::Board::Column::H][Chess::Board::Row(2)] = {SideSelector::White, PieceType::Pawn, PieceSelector::Pawn::H};

    m_occupancyMap[Chess::Board::Column::A][Chess::Board::Row(7)] = {SideSelector::Black, PieceType::Pawn, PieceSelector::Pawn::A};
    m_occupancyMap[Chess::Board::Column::B][Chess::Board::Row(7)] = {SideSelector::Black, PieceType::Pawn, PieceSelector::Pawn::B};
    m_occupancyMap[Chess::Board::Column::C][Chess::Board::Row(7)] = {SideSelector::Black, PieceType::Pawn, PieceSelector::Pawn::C};
    m_occupancyMap[Chess::Board::Column::D][Chess::Board::Row(7)] = {SideSelector::Black, PieceType::Pawn, PieceSelector::Pawn::D};
    m_occupancyMap[Chess::Board::Column::E][Chess::Board::Row(7)] = {SideSelector::Black, PieceType::Pawn, PieceSelector::Pawn::E};
    m_occupancyMap[Chess::Board::Column::F][Chess::Board::Row(7)] = {SideSelector::Black, PieceType::Pawn, PieceSelector::Pawn::F};
    m_occupancyMap[Chess::Board::Column::G][Chess::Board::Row(7)] = {SideSelector::Black, PieceType::Pawn, PieceSelector::Pawn::G};
    m_occupancyMap[Chess::Board::Column::H][Chess::Board::Row(7)] = {SideSelector::Black, PieceType::Pawn, PieceSelector::Pawn::H};

    m_occupancyMap[Chess::Board::Column::A][Chess::Board::Row(8)] = {SideSelector::Black, PieceType::Rook, PieceSelector::Rook::A};
    m_occupancyMap[Chess::Board::Column::B][Chess::Board::Row(8)] = {SideSelector::Black, PieceType::Knight, PieceSelector::Knight::B};
    m_occupancyMap[Chess::Board::Column::C][Chess::Board::Row(8)] = {SideSelector::Black, PieceType::Bishop, PieceSelector::Bishop::C};
    m_occupancyMap[Chess::Board::Column::D][Chess::Board::Row(8)] = {SideSelector::Black, PieceType::King, PieceSelector::King::D};
    m_occupancyMap[Chess::Board::Column::E][Chess::Board::Row(8)] = {SideSelector::Black, PieceType::Queen, PieceSelector::Queen::E};
    m_occupancyMap[Chess::Board::Column::F][Chess::Board::Row(8)] = {SideSelector::Black, PieceType::Bishop, PieceSelector::Bishop::F};
    m_occupancyMap[Chess::Board::Column::G][Chess::Board::Row(8)] = {SideSelector::Black, PieceType::Knight, PieceSelector::Knight::G};
    m_occupancyMap[Chess::Board::Column::H][Chess::Board::Row(8)] = {SideSelector::Black, PieceType::Rook, PieceSelector::Rook::H};
}
Chess::Board::Position Board::getPiecePosition(const Chess::Board::PieceDescription& pieceDescription) const{
    switch (pieceDescription.sideSelector()){
        case Chess::Board::SideSelector::Black: return m_blackSide.getPiece(pieceDescription.type(), pieceDescription.pieceSelector()).currentPosition();
        case Chess::Board::SideSelector::White: return m_whiteSide.getPiece(pieceDescription.type(), pieceDescription.pieceSelector()).currentPosition();
        default: return {Chess::Board::Column::Invalid,Chess::Board::Row{0}};
    }
}

Chess::Board::PieceDescription Board::getPieceAtPosition(const Chess::Board::Position& position) const{
    if(m_occupancyMap.count(position.column()) > 0){
        if(m_occupancyMap.at(position.column()).count(position.row()) > 0){
            return m_occupancyMap.at(position.column()).at(position.row());
        }
    }
    return PieceDescription();
}


Chess::Board::MoveResult Board::movePiece(const Chess::Board::PieceDescription& pieceDescription, const Chess::Board::Position& newPosition){
    auto& side = (pieceDescription.sideSelector() == SideSelector::White)?m_whiteSide:m_blackSide;
    if(!pieceDescription.isValid()){
        return MoveResult{MoveResult::Status::InvalidInput, {{MoveResult::Info::InvalidInput::Type::InvalidPieceSelector, pieceDescription}}};
    }
    if(!newPosition.isValid()){
        return MoveResult{MoveResult::Status::InvalidInput, {{MoveResult::Info::InvalidInput::Type::InvalidPosition, pieceDescription}}};
    }
    
    auto& piece = side.getPiece(pieceDescription.type(), pieceDescription.pieceSelector());
    if(!piece.isValid()){
        return MoveResult{MoveResult::Status::InvalidInput, {{MoveResult::Info::InvalidInput::Type::InvalidPieceSelector, pieceDescription}}};
    }

    auto pieceAtDestinationDescription = getPieceAtPosition(newPosition);

    if(pieceAtDestinationDescription.isValid()){
        bool sameSide = (pieceAtDestinationDescription.sideSelector() == pieceDescription.sideSelector());
        return MoveResult{MoveResult::Status::Collision, {{sameSide, !sameSide, pieceDescription, pieceAtDestinationDescription, newPosition}}};
    }    
        
    auto oldPosition = piece.currentPosition();
    piece.setPosition(newPosition);
    m_occupancyMap.at(oldPosition.column()).erase(oldPosition.row());
    m_occupancyMap[newPosition.column()][newPosition.row()] = pieceDescription;   

    return MoveResult{MoveResult::Status::Ok, {{oldPosition, newPosition}}};
}

}
}