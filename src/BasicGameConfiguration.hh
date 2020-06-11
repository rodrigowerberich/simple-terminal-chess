#pragma once

#include "GameConfigurationInterface.hh"

namespace Chess{

class BasicGameConfiguration: public GameConfigurationInterface{
public:
    const std::string& language() const override;
};

}