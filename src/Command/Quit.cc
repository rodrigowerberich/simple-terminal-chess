#include "Command/Quit.hh"
#include "Output/UserInterface/MessageSelector.hh"

#include <algorithm>

namespace Chess{
namespace Command{

Quit::Quit():
m_quitWord1{"exit"},
m_quitWord2{"quit"}{

}


void Quit::init(Chess::Resources::GameResourcesInterface& gameResources){
    m_quitWord1 = gameResources.messageManager()[Chess::Output::UserInterface::MessageSelector::QUIT_COMMAND_QUIT_WORD_1];
    m_quitWord2 = gameResources.messageManager()[Chess::Output::UserInterface::MessageSelector::QUIT_COMMAND_QUIT_WORD_2];
}


bool Quit::activated(const Chess::Input::ParsedInput& parsedInput){
    if(parsedInput.size() != 1){
        return false;
    }
    auto lowerInput = parsedInput[0];
    std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), [](auto l){return std::tolower(l);});
    return (parsedInput.size() == 1) && ((lowerInput == m_quitWord1) || (lowerInput == m_quitWord2));
}

bool Quit::execute(Chess::Resources::GameResourcesInterface& gameResources){
    return false;
}

}
}