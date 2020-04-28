#pragma once

#include "CommandInterface.hh"

namespace Chess{
namespace Input{
namespace Commands{

class CommandQuit: public Chess::Input::CommandInterface{
public:
    void init(GameResources& gameResources) override;
    bool activated(const std::string& commandLine) override;
    bool execute(GameResources& gameResources) override;
};

}
}
}