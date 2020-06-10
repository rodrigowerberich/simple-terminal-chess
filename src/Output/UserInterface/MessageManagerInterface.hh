#pragma once

#include <string>

namespace Chess{
namespace Output{
namespace UserInterface{

class LanguagePackageInterface{
public:
    virtual const std::string& operator[](const std::string& messageSelector) const = 0;
};

class MessageManagerInterface{
public:
    virtual const LanguagePackageInterface& operator[](const std::string& languageSelector) const = 0;
};

}
}
}