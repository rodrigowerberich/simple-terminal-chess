#pragma once

#include "CommandInterface.hh"

namespace Chess{
namespace Input{
namespace Commands{

class CommandQuit: public Chess::Input::CommandInterface{
    bool activated(const std::string& commandLine) override;
    bool execute() override;
};

}
}
}