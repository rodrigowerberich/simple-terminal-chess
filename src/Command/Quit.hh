#pragma once

#include "CommandInterface.hh"

namespace Chess{
namespace Command{

class Quit: public Chess::Command::CommandInterface{
private:
    std::string m_quitWord1;
    std::string m_quitWord2;
public:
    Quit();
    void init(Chess::Resources::GameResourcesInterface& gameResources) override;
    bool activated(const Chess::Input::ParsedInput& parsedInput) override;
    bool execute(Chess::Resources::GameResourcesInterface& gameResources) override;
};

}
}