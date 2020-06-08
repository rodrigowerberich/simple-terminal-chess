#pragma once

#include <string>

namespace Chess{
namespace Output{
namespace UserInterface{

struct MessageSelector{
    std::string language;
    std::string messageName;
};

namespace LanguageSelector{
    extern const std::string EN;
    extern const std::string PT_BR;
}

namespace MessageNameSelector{
    extern const std::string WELCOME_MESSAGE;
}

extern const std::string ERROR_MESSAGE;

}
}
}