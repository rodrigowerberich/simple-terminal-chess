#pragma once

#include "CommandInterface.hh"
#include "Command/ManagerInterface.hh"

#include <vector>

namespace Chess{
namespace Command{

class Help: public Chess::Command::CommandInterface{
private:
    std::vector<std::string> m_helpWords;
    const ManagerInterface& m_manager;
public:
    Help(const ManagerInterface& manager);
    void init(Chess::Resources::GameResourcesInterface& gameResources) override;
    bool activated(const Chess::Input::ParsedInput& parsedInput) override;
    bool execute(Chess::Resources::GameResourcesInterface& gameResources) override;
    const std::string & helpText() const;
};

}
}