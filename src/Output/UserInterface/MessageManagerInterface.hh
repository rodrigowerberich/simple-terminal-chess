#pragma once

#include <string>
#include <vector>
#include <functional>

namespace Chess{
namespace Output{
namespace UserInterface{

class LanguagePackageInterface{
public:
    using FilterFunction = std::function<bool(const std::string &)>;
    virtual const std::string& operator[](const std::string& messageSelector) const = 0;
    virtual const std::vector<std::string> filterHeaders(const FilterFunction&) const = 0;
};

class MessageManagerInterface{
public:
    virtual const LanguagePackageInterface& operator[](const std::string& languageSelector) const = 0;
};

}
}
}