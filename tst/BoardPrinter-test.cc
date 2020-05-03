#include <sstream>

#include "gtest/gtest.h"
#include "BoardPrinter.hh"
#include "Board.hh"
#include "Printer.hh"

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

    // std::cout << boardPrinted;
    std::stringstream output;
    Printer printer(output);

    Board board;
    BoardPrinter boardPrinter(board);
    printer.print(boardPrinter);
    // std::cout << output.str() << std::endl;
    // std::cout << boardPrinted << std::endl;
    ASSERT_EQ(output.str(), boardPrinted);
}


TEST(XXX,xxx){
    using namespace Chess::Board;
    using namespace Chess::Output;
    Printer printer(std::cout);
    Board board;
    printer.println(BoardPrinter(board));
    board.movePiece({SideSelector::White, PieceType::Pawn, PieceSelector::Pawn::B}, {Column::B, Row{4}});
    printer.println(BoardPrinter(board));
    board.movePiece({SideSelector::White, PieceType::Rook, PieceSelector::Rook::H}, {Column::E, Row{3}});
    printer.println(BoardPrinter(board));
}