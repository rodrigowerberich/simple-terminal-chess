#include "Board/Board.hh"
#include "Board/BoardDefinitions.hh"

namespace Chess{
namespace Board{

template <typename T, typename Description>
void Board_setDefaultPositionOnMap(T& occupancyMap, const Description& description){
    auto defaultPosition = Chess::Board::Definitions::pieceDefaultPosition(description);
    occupancyMap[defaultPosition.column()][defaultPosition.row()] = description;
}

Board::Board():
m_whiteSide{Chess::Board::SideSelector::White},
m_blackSide{Chess::Board::SideSelector::Black}{
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_PA_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_PB_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_PC_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_PD_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_PE_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_PF_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_PG_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_PH_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_RA_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_kB_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_BC_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_QD_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_KE_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_BF_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_kG_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::B_RH_DESCRIPTION);

    
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_PA_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_PB_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_PC_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_PD_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_PE_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_PF_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_PG_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_PH_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_RA_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_kB_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_BC_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_QD_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_KE_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_BF_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_kG_DESCRIPTION);
    Board_setDefaultPositionOnMap(m_occupancyMap, Chess::Board::Definitions::W_RH_DESCRIPTION);
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
        if(pieceAtDestinationDescription == pieceDescription){
            return MoveResult{MoveResult::Status::NoMovement, {MoveResult::Info::NoMovement{}}};
        }
        
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