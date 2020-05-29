#include "gtest/gtest.h"

#include "Board/Comparer.hh"
#include "Board/Definitions.hh"

static constexpr char NORMAL_BOARD[] =
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

static constexpr char MOVED_PA_BOARD[] =
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
| W-PA |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
|      | W-PB | W-PC | W-PD | W-PE | W-PF | W-PG | W-PH |
|______|______|______|______|______|______|______|______|
|      |      |      |      |      |      |      |      |
| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF | W-kG | W-RH |
|______|______|______|______|______|______|______|______|)";

TEST(BoardComparer, normalBoard){
    using namespace Chess::Board;
    Board board;
    ASSERT_TRUE(Comparer::compare(board, NORMAL_BOARD));
    ASSERT_TRUE(Comparer::compare(NORMAL_BOARD, NORMAL_BOARD));
    ASSERT_TRUE(Comparer::compare(board, board));
}

TEST(BoardComparer, differentBoards){
    using namespace Chess::Board;
    Board board;
    Board board1;
    board1.movePiece(Definitions::W_PA_DESCRIPTION, Position{Column::A, 4});
    ASSERT_FALSE(Comparer::compare(board, ""));
    ASSERT_FALSE(Comparer::compare(board, MOVED_PA_BOARD));
    ASSERT_FALSE(Comparer::compare(board1, NORMAL_BOARD));
    ASSERT_FALSE(Comparer::compare("", NORMAL_BOARD));
    ASSERT_FALSE(Comparer::compare(MOVED_PA_BOARD, NORMAL_BOARD));
    ASSERT_FALSE(Comparer::compare(board, board1));
}