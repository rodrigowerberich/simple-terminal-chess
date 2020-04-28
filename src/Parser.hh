#pragma once

#include <istream>
#include <vector>

#include "ParserInterface.hh"
#include "CommandUnrecognized.hh"

namespace Chess{
namespace Input {

class Parser: public Chess::Input::ParserInterface
{
private:
    std::istream& m_inputStream;
    std::vector<std::reference_wrapper<CommandInterface>> m_commands;
    Chess::Input::Commands::CommandUnrecognized m_commandUnrecognized;
public:
    Parser(std::istream& inputStream);
    ~Parser();
    CommandInterface& parse(GameResources& gameResources) override;
    void addCommand(CommandInterface& command) override;
};
}
}