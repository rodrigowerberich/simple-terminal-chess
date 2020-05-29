#pragma once

#include "Input/ParsedInput.hh"

namespace Chess{

namespace Input {

class ParserInterface
{
public:
    virtual ParsedInput parse() const = 0;
};

}
}