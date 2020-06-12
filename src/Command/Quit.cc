#include "Command/Quit.hh"
#include "Output/UserInterface/MessageSelector.hh"

#include <iostream>
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
    std::cout << parsedInput[0] << " " << m_quitWord1 << " " << m_quitWord2 << std::endl;
    return (parsedInput.size() == 1) && ((parsedInput[0] == m_quitWord1) || (parsedInput[0] == m_quitWord2));
}

bool Quit::execute(Chess::Resources::GameResourcesInterface& gameResources){
    return false;
}

}
}