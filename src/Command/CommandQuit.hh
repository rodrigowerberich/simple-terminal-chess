#pragma once

#include "CommandInterface.hh"

namespace Chess{
namespace Command{

class Quit: public Chess::Command::CommandInterface{
public:
    void init(GameResources& gameResources) override;
    bool activated(const Chess::Input::ParsedInput& parsedInput) override;
    bool execute(GameResources& gameResources) override;
};

}
}