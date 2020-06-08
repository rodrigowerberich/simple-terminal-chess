#include "gtest/gtest.h"
#include "Output/UserInterface/VerySimpleMessageManager.hh"

TEST(VerySimpleMessageManager, quickTest) {
    using namespace Chess;

    auto messageManager = Output::UserInterface::VerySimpleMessageManager();
    const auto & messageEn = messageManager[{Output::UserInterface::LanguageSelector::EN, Output::UserInterface::MessageNameSelector::WELCOME_MESSAGE}];
    const auto & messagePtBr = messageManager[{Output::UserInterface::LanguageSelector::PT_BR, Output::UserInterface::MessageNameSelector::WELCOME_MESSAGE}];
    ASSERT_EQ(messageEn, "Hi");
    ASSERT_EQ(messagePtBr, "Oi");

}