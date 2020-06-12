#pragma once

#include <string>

namespace Chess{

class GameConfigurationInterface{
public:
    virtual const std::string& language() const = 0;
    virtual void setLanguage(const std::string& language) = 0;
};

}