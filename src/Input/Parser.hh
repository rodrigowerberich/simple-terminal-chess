#pragma once

#include <istream>

#include "Input/ParserInterface.hh"

namespace Chess{
namespace Input {

class Parser: public Chess::Input::ParserInterface
{
private:
    std::istream& m_inputStream;
public:
    Parser(std::istream& inputStream);
    ~Parser();
    ParsedInput parse() const override;
};
}
}