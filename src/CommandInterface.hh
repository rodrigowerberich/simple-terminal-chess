#pragma once

#include <string>

namespace Chess{
namespace Input {

class CommandInterface{
public:
    virtual bool activated(const std::string& commandLine) = 0;
    virtual bool execute() = 0;
};

}
}