#include "gtest/gtest.h"
#include "GameManager.hh"
#include "Input/Parser.hh"
#include "Output/Printer.hh"
#include "Output/UserInterface/VerySimpleMessageManager.hh"
#include "Output/UserInterface/MessageSelector.hh"

#include <sstream>

#define MACRO_P(_C,_R) Chess::Board::Position{Chess::Board::Column::_C, _R}

TEST(GameManager, oneHorizontalStepGrowing) {
    std::stringstream inputStream;
    std::stringstream outputStream;
    auto parser = Chess::Input::Parser(inputStream);
    auto printer = Chess::Output::Printer(outputStream);
    auto messageManager = Chess::Output::UserInterface::VerySimpleMessageManager();

    auto gameManager = Chess::GameManager(parser, printer, messageManager);
    gameManager.init();
    
    auto bufferContent = messageManager[Chess::Output::UserInterface::LanguageSelector::EN][Chess::Output::UserInterface::MessageSelector::GAME_START_WELCOME_MESSAGE];
    bufferContent += "\n";

    ASSERT_EQ(outputStream.str(), bufferContent);
}