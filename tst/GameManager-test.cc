#include "gtest/gtest.h"
#include "GameManager.hh"
#include "Input/Parser.hh"
#include "Output/Printer.hh"

#include <sstream>

#define MACRO_P(_C,_R) Chess::Board::Position{Chess::Board::Column::_C, _R}

TEST(GameManager, oneHorizontalStepGrowing) {
    std::stringstream inputStream;
    std::stringstream outputStream;
    auto parser = Chess::Input::Parser(inputStream);
    auto printer = Chess::Output::Printer(outputStream);

    auto gameManager = Chess::GameManager(parser, printer);
    gameManager.init();
    ASSERT_EQ(outputStream.str(), "Welcome to simple chess");
}