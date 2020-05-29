#include <sstream>

#include "gtest/gtest.h"
#include "Output/BoardPrinter.hh"
#include "Board/Board.hh"
#include "Output/Printer.hh"

TEST(BoardPrinter, print){
    using namespace Chess::Board;
    using namespace Chess::Output;

    auto boardPrinted = \
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA | W-PB | W-PC | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF | W-kG | W-RH |
|______|______|______|______|______|______|______|______|)";

    std::stringstream output;
    Printer printer(output);

    Board board;
    BoardPrinter boardPrinter(board);
    printer.print(boardPrinter);
    ASSERT_EQ(output.str(), boardPrinted);
}


TEST(BoardPrinter,multipleMoves){
    using namespace Chess::Board;
    using namespace Chess::Output;
auto boardStatus1 = \
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA | W-PB | W-PC | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF | W-kG | W-RH |
|______|______|______|______|______|______|______|______|)";
auto boardStatus2 = \
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      | W-PB |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA |      | W-PC | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF | W-kG | W-RH |
|______|______|______|______|______|______|______|______|)";
auto boardStatus3 = \
R"( ______ ______ ______ ______ ______ ______ ______ ______ 
|      |      |      |      |      |      |      |      |
| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      | W-PB |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      | W-RH |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-PA |      | W-PC | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF | W-kG |      |
|______|______|______|______|______|______|______|______|)";
    std::stringstream output;
    Printer printer(output);
    Board board;
    printer.print(BoardPrinter(board));
    ASSERT_EQ(output.str(), boardStatus1);
    output.str("");
    board.movePiece({SideSelector::White, PieceSelector::Pawn::B}, {Column::B, Row{4}});
    printer.print(BoardPrinter(board));
    ASSERT_EQ(output.str(), boardStatus2);
    output.str("");
    board.movePiece({SideSelector::White, PieceSelector::Rook::H}, {Column::E, Row{3}});
    printer.print(BoardPrinter(board));
    ASSERT_EQ(output.str(), boardStatus3);
}