#pragma once

#include <istream>
#include <vector>

#include "CommandInterface.hh"

namespace Chess{
namespace Input {

class Parser
{
private:
    std::istream& m_inputStream;
    std::vector<std::reference_wrapper<CommandInterface>> m_commands;
public:
    Parser(std::istream& inputStream);
    ~Parser();
    bool parse();
    void addCommand(CommandInterface& command);
};
}
}