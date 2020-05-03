#pragma once

#include "BoardPosition.hh"
#include "Side.hh"
#include "PieceDescription.hh"

namespace Chess{
namespace Board{
    
struct Definitions{

static constexpr int BLACK_FRONT_ROW = Chess::Board::Row{7};
static constexpr int BLACK_BACK_ROW = Chess::Board::Row{8};

static constexpr int WHITE_FRONT_ROW = Chess::Board::Row{2};
static constexpr int WHITE_BACK_ROW = Chess::Board::Row{1};

static constexpr Chess::Board::Position B_PA_POSITION = Chess::Board::Position{Chess::Board::Column::A, BLACK_FRONT_ROW};
static constexpr Chess::Board::Position B_PB_POSITION = Chess::Board::Position{Chess::Board::Column::B, BLACK_FRONT_ROW};
static constexpr Chess::Board::Position B_PC_POSITION = Chess::Board::Position{Chess::Board::Column::C, BLACK_FRONT_ROW};
static constexpr Chess::Board::Position B_PD_POSITION = Chess::Board::Position{Chess::Board::Column::D, BLACK_FRONT_ROW};
static constexpr Chess::Board::Position B_PE_POSITION = Chess::Board::Position{Chess::Board::Column::E, BLACK_FRONT_ROW};
static constexpr Chess::Board::Position B_PF_POSITION = Chess::Board::Position{Chess::Board::Column::F, BLACK_FRONT_ROW};
static constexpr Chess::Board::Position B_PG_POSITION = Chess::Board::Position{Chess::Board::Column::G, BLACK_FRONT_ROW};
static constexpr Chess::Board::Position B_PH_POSITION = Chess::Board::Position{Chess::Board::Column::H, BLACK_FRONT_ROW};
static constexpr Chess::Board::Position B_RA_POSITION = Chess::Board::Position{Chess::Board::Column::A, BLACK_BACK_ROW};
static constexpr Chess::Board::Position B_kB_POSITION = Chess::Board::Position{Chess::Board::Column::B, BLACK_BACK_ROW};
static constexpr Chess::Board::Position B_BC_POSITION = Chess::Board::Position{Chess::Board::Column::C, BLACK_BACK_ROW};
static constexpr Chess::Board::Position B_QD_POSITION = Chess::Board::Position{Chess::Board::Column::D, BLACK_BACK_ROW};
static constexpr Chess::Board::Position B_KE_POSITION = Chess::Board::Position{Chess::Board::Column::E, BLACK_BACK_ROW};
static constexpr Chess::Board::Position B_BF_POSITION = Chess::Board::Position{Chess::Board::Column::F, BLACK_BACK_ROW};
static constexpr Chess::Board::Position B_kG_POSITION = Chess::Board::Position{Chess::Board::Column::G, BLACK_BACK_ROW};
static constexpr Chess::Board::Position B_RH_POSITION = Chess::Board::Position{Chess::Board::Column::H, BLACK_BACK_ROW};

static constexpr Chess::Board::Position W_PA_POSITION = Chess::Board::Position{Chess::Board::Column::A, WHITE_FRONT_ROW};
static constexpr Chess::Board::Position W_PB_POSITION = Chess::Board::Position{Chess::Board::Column::B, WHITE_FRONT_ROW};
static constexpr Chess::Board::Position W_PC_POSITION = Chess::Board::Position{Chess::Board::Column::C, WHITE_FRONT_ROW};
static constexpr Chess::Board::Position W_PD_POSITION = Chess::Board::Position{Chess::Board::Column::D, WHITE_FRONT_ROW};
static constexpr Chess::Board::Position W_PE_POSITION = Chess::Board::Position{Chess::Board::Column::E, WHITE_FRONT_ROW};
static constexpr Chess::Board::Position W_PF_POSITION = Chess::Board::Position{Chess::Board::Column::F, WHITE_FRONT_ROW};
static constexpr Chess::Board::Position W_PG_POSITION = Chess::Board::Position{Chess::Board::Column::G, WHITE_FRONT_ROW};
static constexpr Chess::Board::Position W_PH_POSITION = Chess::Board::Position{Chess::Board::Column::H, WHITE_FRONT_ROW};
static constexpr Chess::Board::Position W_RA_POSITION = Chess::Board::Position{Chess::Board::Column::A, WHITE_BACK_ROW};
static constexpr Chess::Board::Position W_kB_POSITION = Chess::Board::Position{Chess::Board::Column::B, WHITE_BACK_ROW};
static constexpr Chess::Board::Position W_BC_POSITION = Chess::Board::Position{Chess::Board::Column::C, WHITE_BACK_ROW};
static constexpr Chess::Board::Position W_QD_POSITION = Chess::Board::Position{Chess::Board::Column::D, WHITE_BACK_ROW};
static constexpr Chess::Board::Position W_KE_POSITION = Chess::Board::Position{Chess::Board::Column::E, WHITE_BACK_ROW};
static constexpr Chess::Board::Position W_BF_POSITION = Chess::Board::Position{Chess::Board::Column::F, WHITE_BACK_ROW};
static constexpr Chess::Board::Position W_kG_POSITION = Chess::Board::Position{Chess::Board::Column::G, WHITE_BACK_ROW};
static constexpr Chess::Board::Position W_RH_POSITION = Chess::Board::Position{Chess::Board::Column::H, WHITE_BACK_ROW};

static constexpr Chess::Board::PieceDescription B_PA_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::Pawn::A};
static constexpr Chess::Board::PieceDescription B_PB_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::Pawn::B};
static constexpr Chess::Board::PieceDescription B_PC_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::Pawn::C};
static constexpr Chess::Board::PieceDescription B_PD_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::Pawn::D};
static constexpr Chess::Board::PieceDescription B_PE_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::Pawn::E};
static constexpr Chess::Board::PieceDescription B_PF_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::Pawn::F};
static constexpr Chess::Board::PieceDescription B_PG_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::Pawn::G};
static constexpr Chess::Board::PieceDescription B_PH_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::Pawn::H};
static constexpr Chess::Board::PieceDescription B_RA_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::Rook::A};
static constexpr Chess::Board::PieceDescription B_kB_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::Knight::B};
static constexpr Chess::Board::PieceDescription B_BC_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::Bishop::C};
static constexpr Chess::Board::PieceDescription B_QD_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::Queen::D};
static constexpr Chess::Board::PieceDescription B_KE_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::King::E};
static constexpr Chess::Board::PieceDescription B_BF_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::Bishop::F};
static constexpr Chess::Board::PieceDescription B_kG_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::Knight::G};
static constexpr Chess::Board::PieceDescription B_RH_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::Black, Chess::Board::PieceSelector::Rook::H};

static constexpr Chess::Board::PieceDescription W_PA_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::Pawn::A};
static constexpr Chess::Board::PieceDescription W_PB_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::Pawn::B};
static constexpr Chess::Board::PieceDescription W_PC_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::Pawn::C};
static constexpr Chess::Board::PieceDescription W_PD_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::Pawn::D};
static constexpr Chess::Board::PieceDescription W_PE_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::Pawn::E};
static constexpr Chess::Board::PieceDescription W_PF_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::Pawn::F};
static constexpr Chess::Board::PieceDescription W_PG_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::Pawn::G};
static constexpr Chess::Board::PieceDescription W_PH_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::Pawn::H};
static constexpr Chess::Board::PieceDescription W_RA_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::Rook::A};
static constexpr Chess::Board::PieceDescription W_kB_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::Knight::B};
static constexpr Chess::Board::PieceDescription W_BC_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::Bishop::C};
static constexpr Chess::Board::PieceDescription W_QD_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::Queen::D};
static constexpr Chess::Board::PieceDescription W_KE_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::King::E};
static constexpr Chess::Board::PieceDescription W_BF_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::Bishop::F};
static constexpr Chess::Board::PieceDescription W_kG_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::Knight::G};
static constexpr Chess::Board::PieceDescription W_RH_DESCRIPTION = Chess::Board::PieceDescription{Chess::Board::SideSelector::White, Chess::Board::PieceSelector::Rook::H};

#define MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(_desc,_X)\
    if (_desc == _X##_DESCRIPTION){ return _X##_POSITION; }

static constexpr Chess::Board::Position pieceDefaultPosition(const Chess::Board::PieceDescription & description){
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_PA);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_PB);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_PC);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_PD);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_PE);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_PF);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_PG);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_PH);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_RA);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_kB);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_BC);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_QD);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_KE);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_BF);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_kG);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, B_RH);

    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_PA);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_PB);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_PC);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_PD);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_PE);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_PF);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_PG);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_PH);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_RA);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_kB);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_BC);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_QD);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_KE);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_BF);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_kG);
    MACRO_BOARD_DEFINTIONS_DESCRIPTION_TO_POSITION(description, W_RH);

    return  {Chess::Board::Column::Invalid, -1};
}

};

}
}