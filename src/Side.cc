#include "Side.hh"

namespace Chess{
namespace Board{

Side::Side(Board::SideSelector sideSelected):
    m_invalidPiece{PieceType::Pawn}{
    m_sideSelected = sideSelected;
    auto frontRow = Board::Row{0};
    auto backRow = Board::Row{0};
    if(m_sideSelected == Board::SideSelector::White){
        backRow = Board::Row{WHITE_BACK_ROW};
        frontRow = Board::Row{WHITE_FRONT_ROW};
    }else{
        backRow = Board::Row{BLACK_BACK_ROW};
        frontRow = Board::Row{BLACK_FRONT_ROW};
    }
    // Putting the pawns in their board positions
    auto pawns = std::vector<Board::Piece>{
        {PieceType::Pawn, {Column::A, frontRow}},
        {PieceType::Pawn, {Column::B, frontRow}},
        {PieceType::Pawn, {Column::C, frontRow}},
        {PieceType::Pawn, {Column::D, frontRow}},
        {PieceType::Pawn, {Column::E, frontRow}},
        {PieceType::Pawn, {Column::F, frontRow}},
        {PieceType::Pawn, {Column::G, frontRow}},
        {PieceType::Pawn, {Column::H, frontRow}}
    };
    m_pieces.emplace(PieceType::Pawn, pawns);
    // Putting the rooks in their board positions
    auto rooks = std::vector<Board::Piece>{
        {PieceType::Rook, {Column::A, backRow}},
        {PieceType::Rook, {Column::H, backRow}}
    };
    m_pieces.emplace(PieceType::Rook, rooks);
    // Putting the knights in their board positions
    auto knights = std::vector<Board::Piece>{
        {PieceType::Knight, {Column::B, backRow}},
        {PieceType::Knight, {Column::G, backRow}}
    };
    m_pieces.emplace(PieceType::Knight, knights);
    // Putting the bishops in their board positions
    auto bishops = std::vector<Board::Piece>{
        {PieceType::Bishop, {Column::C, backRow}},
        {PieceType::Bishop, {Column::F, backRow}}
    };
    m_pieces.emplace(PieceType::Bishop, bishops);
    // Putting the queen in her board position
    auto queen = std::vector<Board::Piece>{
        {PieceType::Queen, {Column::E, backRow}}
    };
    m_pieces.emplace(PieceType::Queen, queen);
    // Putting the king in his board position
    auto king = std::vector<Board::Piece>{
        {PieceType::King, {Column::D, backRow}}
    };
    m_pieces.emplace(PieceType::King, king);
}
Board::Piece& Side::getPiece(PieceType type, const PieceSelector& pieceSelector){
    auto& piecesFromAType = m_pieces[type];
    switch(type){
        case PieceType::Pawn:
            return piecesFromAType[static_cast<size_t>(pieceSelector.pawn)];
        case PieceType::Rook:
            return piecesFromAType[static_cast<size_t>(pieceSelector.rook)];
        case PieceType::Knight:
            return piecesFromAType[static_cast<size_t>(pieceSelector.knight)];
        case PieceType::Bishop:
            return piecesFromAType[static_cast<size_t>(pieceSelector.bishop)];
        case PieceType::Queen:
            return piecesFromAType[static_cast<size_t>(pieceSelector.queen)];
        case PieceType::King:
            return piecesFromAType[static_cast<size_t>(pieceSelector.king)];
        default:
            return m_invalidPiece;
    }
}

}
}