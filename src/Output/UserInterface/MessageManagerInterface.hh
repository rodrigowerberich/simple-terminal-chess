#pragma once

#include "Output/UserInterface/MessageSelector.hh"

namespace Chess{
namespace Output{
namespace UserInterface{

class MessageManagerInterface{
public:
    virtual const std::string& operator[](const MessageSelector& selector) const = 0;
};

}
}
}