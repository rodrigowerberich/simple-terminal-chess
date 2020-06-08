# pragma once

#include "Output/UserInterface/MessageManagerInterface.hh"

#include <map>

namespace Chess{
namespace Output{
namespace UserInterface{


class VerySimpleMessageManager: public MessageManagerInterface{
private:
    std::map<std::string, std::map<std::string, std::string>> m_messages;
public:
    VerySimpleMessageManager();
    const std::string& operator[](const MessageSelector& selector) const override;
};

}
}
}