#pragma once

#include "CommandInterface.hh"

#include <vector>

namespace Chess{
namespace Command{

class Quit: public Chess::Command::CommandInterface{
private:
    std::vector<std::string> m_quitWords;
public:
    Quit();
    void init(Chess::Resources::GameResourcesInterface& gameResources) override;
    bool activated(const Chess::Input::ParsedInput& parsedInput) override;
    bool execute(Chess::Resources::GameResourcesInterface& gameResources) override;
};

}
}