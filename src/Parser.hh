#pragma once

#include <istream>
#include <vector>

#include "ParserInterface.hh"

namespace Chess{
namespace Input {

class Parser: public Chess::Input::ParserInterface
{
private:
    std::istream& m_inputStream;
    std::vector<std::reference_wrapper<CommandInterface>> m_commands;
public:
    Parser(std::istream& inputStream);
    ~Parser();
    bool parse(GameResources& gameResources) override;
    void addCommand(CommandInterface& command) override;
};
}
}