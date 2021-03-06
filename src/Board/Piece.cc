#include "Board/Piece.hh"

#include <ostream>

namespace Chess{
namespace Board{

template <>
int PieceSelector::toIndex<PieceType::Pawn, PieceSelector::Pawn>(PieceSelector::Pawn pawn){
    switch (pawn){
        case PieceSelector::Pawn::A: return 0;
        case PieceSelector::Pawn::B: return 1;
        case PieceSelector::Pawn::C: return 2;
        case PieceSelector::Pawn::D: return 3;
        case PieceSelector::Pawn::E: return 4;
        case PieceSelector::Pawn::F: return 5;
        case PieceSelector::Pawn::G: return 6;
        case PieceSelector::Pawn::H: return 7;
        default: return -1;
    }
}

template <>
int PieceSelector::toIndex<PieceType::Rook, PieceSelector::Rook>(PieceSelector::Rook rook){
    switch (rook){
        case PieceSelector::Rook::A : return 0;
        case PieceSelector::Rook::H : return 1;
        default: return -1;
    }
}

template <>
int PieceSelector::toIndex<PieceType::Knight, PieceSelector::Knight>(PieceSelector::Knight knight){
    switch (knight){
        case PieceSelector::Knight::B: return 0;
        case PieceSelector::Knight::G: return 1;
        default: return -1;
    }
}


template <>
int PieceSelector::toIndex<PieceType::Bishop, PieceSelector::Bishop>(PieceSelector::Bishop bishop){
    switch (bishop){
        case PieceSelector::Bishop::C: return 0;
        case PieceSelector::Bishop::F: return 1;
        default: return -1;
    }
}

template <>
int PieceSelector::toIndex<PieceType::Queen, PieceSelector::Queen>(PieceSelector::Queen queen){
    switch (queen){
        case PieceSelector::Queen::D: return 0;
        default: return -1;
    }
}

template <>
int PieceSelector::toIndex<PieceType::King, PieceSelector::King>(PieceSelector::King king){
    switch (king){
        case PieceSelector::King::E: return 0;
        default: return -1;
    }
}

template <>
std::string PieceSelector::toString<PieceType::Pawn, PieceSelector::Pawn>(PieceSelector::Pawn pawn){
    switch (pawn){
        case PieceSelector::Pawn::A: return "A";
        case PieceSelector::Pawn::B: return "B";
        case PieceSelector::Pawn::C: return "C";
        case PieceSelector::Pawn::D: return "D";
        case PieceSelector::Pawn::E: return "E";
        case PieceSelector::Pawn::F: return "F";
        case PieceSelector::Pawn::G: return "G";
        case PieceSelector::Pawn::H: return "H";
        default: return "";
    }
}

template <>
std::string PieceSelector::toString<PieceType::Rook, PieceSelector::Rook>(PieceSelector::Rook rook){
    switch (rook){
        case PieceSelector::Rook::A : return "A";
        case PieceSelector::Rook::H : return "H";
        default: return "";
    }
}

template <>
std::string PieceSelector::toString<PieceType::Knight, PieceSelector::Knight>(PieceSelector::Knight knight){
    switch (knight){
        case PieceSelector::Knight::B: return "B";
        case PieceSelector::Knight::G: return "G";
        default: return "";
    }
}


template <>
std::string PieceSelector::toString<PieceType::Bishop, PieceSelector::Bishop>(PieceSelector::Bishop bishop){
    switch (bishop){
        case PieceSelector::Bishop::C: return "C";
        case PieceSelector::Bishop::F: return "F";
        default: return "";
    }
}

template <>
std::string PieceSelector::toString<PieceType::Queen, PieceSelector::Queen>(PieceSelector::Queen queen){
    switch (queen){
        case PieceSelector::Queen::D: return " ";
        default: return "";
    }
}

template <>
std::string PieceSelector::toString<PieceType::King, PieceSelector::King>(PieceSelector::King king){
    switch (king){
        case PieceSelector::King::E: return " ";
        default: return "";
    }
}

std::string Board::PieceSelector::toString(PieceType type) const{
    switch(type){
        case PieceType::Pawn:   return toString<PieceType::Pawn>(pawn);
        case PieceType::Rook:   return toString<PieceType::Rook>(rook);
        case PieceType::Knight: return toString<PieceType::Knight>(knight);
        case PieceType::Bishop: return toString<PieceType::Bishop>(bishop);
        case PieceType::Queen:  return toString<PieceType::Queen>(queen);
        case PieceType::King:   return toString<PieceType::King>(king);
        default: return "";
    }
}

int Board::PieceSelector::toIndex(PieceType type) const{
    switch(type){
        case PieceType::Pawn: return toIndex<PieceType::Pawn>(pawn);
        case PieceType::Rook: return toIndex<PieceType::Rook>(rook);
        case PieceType::Knight: return toIndex<PieceType::Knight>(knight);
        case PieceType::Bishop: return toIndex<PieceType::Bishop>(bishop);
        case PieceType::Queen: return toIndex<PieceType::Queen>(queen);
        case PieceType::King: return toIndex<PieceType::King>(king);
        default: return -1;
    }
}  

std::vector<Chess::Board::PieceType> PieceType_asVector(){
    using namespace Chess;
    return {    
        Board::PieceType::Pawn,
        Board::PieceType::Rook,
        Board::PieceType::Knight,
        Board::PieceType::Bishop,
        Board::PieceType::Queen,
        Board::PieceType::King
    };
}

Chess::Board::Piece::Piece(
    Chess::Board::PieceType type, 
    Chess::Board::Position position):
    m_type{type},
    m_position{position}{

}
Chess::Board::PieceType Chess::Board::Piece::type() const{
    return m_type;
}
const Chess::Board::Position& Chess::Board::Piece::currentPosition() const{
    return m_position;
}
void Chess::Board::Piece::setPosition(const Chess::Board::Position& position){
    m_position = position;
}

bool Chess::Board::Piece::isValid() const{
    return (m_type != Chess::Board::PieceType::Invalid);
}
bool Chess::Board::Piece::isOnBoard() const{
    return m_position.isValid();
}


}
}

std::ostream& operator<<(std::ostream& os, const Chess::Board::PieceType& type){
    switch(type){
        case Chess::Board::PieceType::Pawn:{
            os << "P";
            break;
        }
        case Chess::Board::PieceType::Rook:{
            os << "R";
            break;
        }
        case Chess::Board::PieceType::Knight:{
            os << "k";
            break;
        }
        case Chess::Board::PieceType::Bishop:{
            os << "B";
            break;
        }
        case Chess::Board::PieceType::Queen:{
            os << "Q";
            break;
        }
        case Chess::Board::PieceType::King:{
            os << "K";
            break;
        }
        default: {
            os << "Invalid";
            break;
        }        
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Chess::Board::Piece& piece){
    os << "{\"type\":\"" << piece.type() << "\",\"position\":\"" << piece.currentPosition() << "\"}"; 
    return os;
}