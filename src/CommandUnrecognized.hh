#pragma once

#include <string>

#include "CommandInterface.hh"

namespace Chess{
namespace Input{
namespace Commands{

class CommandUnrecognized: public Chess::Input::CommandInterface{
private:
    std::string m_unrecognizedCommandString;
public:
    void init(GameResources& gameResources) override;
    bool activated(const std::string& commandLine) override;
    bool execute(GameResources& gameResources) override;
    void setUnrecognizedString(const std::string& unrecognizedCommandString);
};

}
}
}