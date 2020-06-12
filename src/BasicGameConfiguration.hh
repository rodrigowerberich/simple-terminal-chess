#pragma once

#include "GameConfigurationInterface.hh"

namespace Chess{

class BasicGameConfiguration: public GameConfigurationInterface{
private:
    std::string m_language;
public:
    BasicGameConfiguration();
    const std::string& language() const override;
    void setLanguage(const std::string& language) override;
};

}