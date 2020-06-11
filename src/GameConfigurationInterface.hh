#pragma once

#include <string>

namespace Chess{

class GameConfigurationInterface{
public:
    virtual const std::string& language() const = 0;
};

}