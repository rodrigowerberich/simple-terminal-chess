#pragma once

#include "ParsedInput.hh"

namespace Chess{

namespace Input {

class ParserInterface
{
public:
    virtual ParsedInput parse() = 0;
};

}
}