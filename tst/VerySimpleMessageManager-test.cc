#include "gtest/gtest.h"
#include "Output/UserInterface/VerySimpleMessageManager.hh"
#include "Output/UserInterface/MessageSelector.hh"

TEST(VerySimpleMessageManager, quickTest) {
    using namespace Chess;

    auto messageManager = Output::UserInterface::VerySimpleMessageManager();
    ASSERT_EQ(messageManager[Output::UserInterface::LanguageSelector::EN][Output::UserInterface::MessageNameSelector::WELCOME_MESSAGE], "Hi");
    ASSERT_EQ(messageManager[Output::UserInterface::LanguageSelector::PT_BR][Output::UserInterface::MessageNameSelector::WELCOME_MESSAGE], "Oi");
    ASSERT_EQ(messageManager["Banana"][Output::UserInterface::MessageNameSelector::WELCOME_MESSAGE], Output::UserInterface::ERROR_MESSAGE);
    ASSERT_EQ(messageManager[Output::UserInterface::LanguageSelector::PT_BR]["No message"], Output::UserInterface::ERROR_MESSAGE);
}