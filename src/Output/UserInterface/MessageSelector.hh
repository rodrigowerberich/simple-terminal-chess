#pragma once

#include <string>

namespace Chess{
namespace Output{
namespace UserInterface{

namespace LanguageSelector{
    extern const std::string EN;
    extern const std::string PT_BR;
}

namespace MessageSelector{
    extern const std::string WELCOME_MESSAGE;
    extern const std::string GAME_START_WELCOME_MESSAGE;

    extern const std::string QUIT_COMMAND_QUIT_WORD_1;
    extern const std::string QUIT_COMMAND_QUIT_WORD_2;
    extern const std::string QUIT_COMMAND_HELP_BEFORE_MESSAGE;
    extern const std::string QUIT_COMMAND_HELP_AFTER_MESSAGE;

    extern const std::string BEFORE_UNRECOGNIZED_INPUT_MESSAGE;
    extern const std::string AFTER_UNRECOGNIZED_INPUT_MESSAGE;

    extern const std::string HELP_COMMAND_HELP_WORD_1;
}


extern const std::string ERROR_MESSAGE;

}
}
}