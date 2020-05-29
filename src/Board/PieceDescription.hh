#pragma once

#include "Board/Piece.hh"
#include "Board/Side.hh"

namespace Chess{
namespace Board{

class PieceDescription{
private:
    Chess::Board::SideSelector m_sideSelector;
    Chess::Board::PieceType m_type;
    Chess::Board::PieceSelector m_pieceSelector;
    Chess::Board::PieceType m_pieceSelectorType;
public:
    PieceDescription();
    
    constexpr PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceSelector::Pawn pawnSelector):
    m_sideSelector{side}, 
    m_type{PieceType::Pawn}, 
    m_pieceSelector{pawnSelector},
    m_pieceSelectorType{PieceType::Pawn}{}
    constexpr PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceSelector::Rook rookSelector):
    m_sideSelector{side}, 
    m_type{PieceType::Rook}, 
    m_pieceSelector{rookSelector},
    m_pieceSelectorType{PieceType::Rook}{}
    constexpr PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceSelector::Knight knightSelector):
    m_sideSelector{side}, 
    m_type{PieceType::Knight}, 
    m_pieceSelector{knightSelector},
    m_pieceSelectorType{PieceType::Knight}{}
    constexpr PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceSelector::Bishop bishopSelector):
    m_sideSelector{side}, 
    m_type{PieceType::Bishop}, 
    m_pieceSelector{bishopSelector},
    m_pieceSelectorType{PieceType::Bishop}{}
    constexpr PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceSelector::Queen queenSelector):
    m_sideSelector{side}, 
    m_type{PieceType::Queen}, 
    m_pieceSelector{queenSelector},
    m_pieceSelectorType{PieceType::Queen}{}
    constexpr PieceDescription(Chess::Board::SideSelector side, Chess::Board::PieceSelector::King kingSelector):
    m_sideSelector{side}, 
    m_type{PieceType::King}, 
    m_pieceSelector{kingSelector},
    m_pieceSelectorType{PieceType::King}{}

    Chess::Board::SideSelector sideSelector() const;
    Chess::Board::PieceType type() const;
    Chess::Board::PieceSelector pieceSelector() const;
    Chess::Board::PieceType pieceSelectorType() const;
    bool isValid() const;
    constexpr bool operator==(const PieceDescription& rhs) const{
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
};

}
}

std::ostream& operator<<(std::ostream& os, const Chess::Board::PieceDescription& pieceDescription);