#include "Side.hh"
#include "BoardDefinitions.hh"

namespace Chess{
namespace Board{

Side::Side(Board::SideSelector sideSelected):
    m_invalidPiece{PieceType::Invalid}{
    m_sideSelected = sideSelected;
    // Putting the pawns in their board positions
    auto pawns = std::vector<Board::Piece>{
        {PieceType::Pawn, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::Pawn::A})},
        {PieceType::Pawn, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::Pawn::B})},
        {PieceType::Pawn, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::Pawn::C})},
        {PieceType::Pawn, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::Pawn::D})},
        {PieceType::Pawn, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::Pawn::E})},
        {PieceType::Pawn, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::Pawn::F})},
        {PieceType::Pawn, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::Pawn::G})},
        {PieceType::Pawn, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::Pawn::H})}
    };
    m_pieces.emplace(PieceType::Pawn, pawns);
    // Putting the rooks in their board positions
    auto rooks = std::vector<Board::Piece>{
        {PieceType::Rook, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::Rook::A})},
        {PieceType::Rook, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::Rook::H})},
    };
    m_pieces.emplace(PieceType::Rook, rooks);
    // Putting the knights in their board positions
    auto knights = std::vector<Board::Piece>{
        {PieceType::Knight, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::Knight::B})},
        {PieceType::Knight, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::Knight::G})},
    };
    m_pieces.emplace(PieceType::Knight, knights);
    // Putting the bishops in their board positions
    auto bishops = std::vector<Board::Piece>{
        {PieceType::Bishop, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::Bishop::C})},
        {PieceType::Bishop, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::Bishop::F})},
    };
    m_pieces.emplace(PieceType::Bishop, bishops);
    // Putting the queen in her board position
    auto queen = std::vector<Board::Piece>{
        {PieceType::Queen, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::Queen::D})}
    };
    m_pieces.emplace(PieceType::Queen, queen);
    // Putting the king in his board position
    auto king = std::vector<Board::Piece>{
        {PieceType::King, Board::Definitions::pieceDefaultPosition({sideSelected, PieceSelector::King::E})}
    };
    m_pieces.emplace(PieceType::King, king);
}
Board::Piece& Side::getPiece(PieceType type, const PieceSelector& pieceSelector){
    auto index = pieceSelector.toIndex(type);
    if(index < 0){
        return m_invalidPiece;
    }else{
        return m_pieces[type][index];
    }
}

const Board::Piece& Side::getPiece(PieceType type, const PieceSelector& pieceSelector) const{
    auto index = pieceSelector.toIndex(type);
    if(index < 0){
        return m_invalidPiece;
    }else{
        return m_pieces.at(type)[index];
    }
}

}
}

std::ostream& operator<<(std::ostream& os, const Chess::Board::SideSelector& sideSelector){
    switch (sideSelector)
    {
    case Chess::Board::SideSelector::Black: {
        os << "B";
        break;
    }
    case Chess::Board::SideSelector::White: {
        os << "W";
        break;
    }
    default:
        break;
    }
    return os;
}
