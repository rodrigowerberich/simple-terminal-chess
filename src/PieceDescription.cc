#include "PieceDescription.hh"

namespace Chess{
namespace Board{

PieceDescription::PieceDescription():
m_sideSelector{SideSelector::White},
m_type{PieceType::Invalid},
m_pieceSelector{PieceSelector::Pawn::A},
m_pieceSelectorType{PieceType::Pawn}{

}


PieceDescription::PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceType pieceType, Chess::Board::PieceSelector::Pawn pawnSelector):
m_sideSelector{side},
m_type{pieceType},
m_pieceSelector{pawnSelector},
m_pieceSelectorType{Chess::Board::PieceType::Pawn}{

}
PieceDescription::PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceType pieceType, Chess::Board::PieceSelector::Rook rookSelector):
m_sideSelector{side},
m_type{pieceType},
m_pieceSelector{rookSelector},
m_pieceSelectorType{Chess::Board::PieceType::Rook}{

}
PieceDescription::PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceType pieceType, Chess::Board::PieceSelector::Knight knightSelector):
m_sideSelector{side},
m_type{pieceType},
m_pieceSelector{knightSelector},
m_pieceSelectorType{Chess::Board::PieceType::Knight}{

}
PieceDescription::PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceType pieceType, Chess::Board::PieceSelector::Bishop bishopSelector):
m_sideSelector{side},
m_type{pieceType},
m_pieceSelector{bishopSelector},
m_pieceSelectorType{Chess::Board::PieceType::Bishop}{

}
PieceDescription::PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceType pieceType, Chess::Board::PieceSelector::Queen queenSelector):
m_sideSelector{side},
m_type{pieceType},
m_pieceSelector{queenSelector},
m_pieceSelectorType{Chess::Board::PieceType::Queen}{

}
PieceDescription::PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceType pieceType, Chess::Board::PieceSelector::King kingSelector):
m_sideSelector{side},
m_type{pieceType},
m_pieceSelector{kingSelector},
m_pieceSelectorType{Chess::Board::PieceType::King}{

}


Chess::Board::SideSelector PieceDescription::sideSelector() const{
    return m_sideSelector;
}
Chess::Board::PieceType PieceDescription::type() const{
    return m_type;
}
Chess::Board::PieceSelector PieceDescription::pieceSelector() const{
    return m_pieceSelector;
}
Chess::Board::PieceType PieceDescription::pieceSelectorType() const{
    return m_pieceSelectorType;
}
bool PieceDescription::isValid() const{
    return m_pieceSelectorType == m_type;
}
bool PieceDescription::operator==(const PieceDescription& rhs) const{
    bool part1 = (m_sideSelector == rhs.m_sideSelector) && 
            (m_type == rhs.m_type) &&
            (m_pieceSelectorType == m_pieceSelectorType);
    if(!part1){
        return false;
    } 
    switch (m_type){
    case PieceType::Rook: return m_pieceSelector.rook == rhs.m_pieceSelector.rook;
    case PieceType::Knight: return m_pieceSelector.knight == rhs.m_pieceSelector.knight;
    case PieceType::Bishop: return m_pieceSelector.bishop == rhs.m_pieceSelector.bishop;
    case PieceType::Pawn: return m_pieceSelector.pawn == rhs.m_pieceSelector.pawn;
    case PieceType::Queen: return m_pieceSelector.queen == rhs.m_pieceSelector.queen;
    case PieceType::King: return m_pieceSelector.king == rhs.m_pieceSelector.king;
    default: return true;
    }

}

}
}