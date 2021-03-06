#pragma once

#include "CommandInterface.hh"

#include <vector>

namespace Chess{
namespace Command{

class Quit: public Chess::Command::CommandInterface{
private:
    std::vector<std::string> m_quitWords;
    std::string m_helpText;
public:
    Quit();
    void init(Chess::Resources::GameResourcesInterface& gameResources) override;
    bool activated(const Chess::Input::ParsedInput& parsedInput) override;
    bool execute(Chess::Resources::GameResourcesInterface& gameResources) override;
    const std::string & helpText() const;

};

}
}