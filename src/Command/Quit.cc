#include "Command/Quit.hh"
#include "Output/UserInterface/MessageSelector.hh"

#include <algorithm>
#include <regex>
#include <functional>

namespace Chess{
namespace Command{

Quit::Quit():
m_quitWords{"exit", "quit"},
m_helpText{""}{
}


void Quit::init(Chess::Resources::GameResourcesInterface& gameResources){
    m_quitWords.clear();
    m_helpText = "";
    auto quitWordNames = gameResources.messageManager().filterHeaders([](const auto& messageName){
        return std::regex_match(messageName, std::regex("QUIT COMMAND QUIT WORD \\d*"));
    });

    m_helpText += gameResources.messageManager()[Chess::Output::UserInterface::MessageSelector::QUIT_COMMAND_HELP_BEFORE_MESSAGE];

    for(const auto & quitWordName:quitWordNames){
        auto quitWord = gameResources.messageManager()[quitWordName];
        std::transform(quitWord.begin(), quitWord.end(), quitWord.begin(), [](auto l){return std::tolower(l);});
        m_quitWords.push_back(quitWord);
        
        
        m_helpText+= "\"" + quitWord + "\"";
        if (quitWordName != quitWordNames.back()){
            m_helpText += ", ";
        }
    }

    m_helpText += gameResources.messageManager()[Chess::Output::UserInterface::MessageSelector::QUIT_COMMAND_HELP_AFTER_MESSAGE];
}


bool Quit::activated(const Chess::Input::ParsedInput& parsedInput){
    if(parsedInput.size() != 1){
        return false;
    }
    auto lowerInput = parsedInput[0];
    std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), [](auto l){return std::tolower(l);});
    bool ok = std::any_of(m_quitWords.begin(), m_quitWords.end(), [&lowerInput](auto& quitWord){ return lowerInput == quitWord; });
    return ok;
}

bool Quit::execute(Chess::Resources::GameResourcesInterface& gameResources){
    return false;
}

const std::string & Quit::helpText() const{
    return m_helpText;
}


}
}