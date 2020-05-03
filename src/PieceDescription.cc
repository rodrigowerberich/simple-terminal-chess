#include "PieceDescription.hh"

namespace Chess{
namespace Board{

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

}
}