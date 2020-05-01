#include "Piece.hh"

#include <ostream>

namespace Chess{
namespace Board{

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

}
}

std::ostream& operator<<(std::ostream& os, const Chess::Board::PieceType& type){
    switch(type){
        case Chess::Board::PieceType::Pawn:{
            os << "Pawn";
            break;
        }
        case Chess::Board::PieceType::Rook:{
            os << "Rook";
            break;
        }
        case Chess::Board::PieceType::Knight:{
            os << "Knight";
            break;
        }
        case Chess::Board::PieceType::Bishop:{
            os << "Bishop";
            break;
        }
        case Chess::Board::PieceType::Queen:{
            os << "Queen";
            break;
        }
        case Chess::Board::PieceType::King:{
            os << "King";
            break;
        }        
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Chess::Board::Piece& piece){
    os << "{\"type\":\"" << piece.type() << "\",\"position\":\"" << piece.currentPosition() << "\"}"; 
    return os;
}