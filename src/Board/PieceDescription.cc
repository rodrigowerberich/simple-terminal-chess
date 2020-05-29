#include "Board/PieceDescription.hh"

namespace Chess{
namespace Board{

PieceDescription::PieceDescription():
m_sideSelector{SideSelector::White},
m_type{PieceType::Invalid},
m_pieceSelector{PieceSelector::Pawn::A},
m_pieceSelectorType{PieceType::Pawn}{
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

}
}

std::ostream& operator<<(std::ostream& os, const Chess::Board::PieceDescription& pieceDescription){
    os << pieceDescription.type();
    return os;
}
