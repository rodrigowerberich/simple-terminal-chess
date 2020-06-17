#include "Command/Help.hh"
#include "Output/UserInterface/MessageSelector.hh"

#include <algorithm>
#include <regex>
#include <functional>

namespace Chess{
namespace Command{

Help::Help(const ManagerInterface& manager):
m_helpWords{"help"},
m_manager{manager}{
}


void Help::init(Chess::Resources::GameResourcesInterface& gameResources){
    m_helpWords.clear();
    auto helpWordNames = gameResources.messageManager().filterHeaders([](const auto& messageName){
        return std::regex_match(messageName, std::regex("HELP COMMAND HELP WORD \\d*"));
    });
    for(const auto & helpWordName:helpWordNames){
        auto helpWord = gameResources.messageManager()[helpWordName];
        std::transform(helpWord.begin(), helpWord.end(), helpWord.begin(), [](auto l){return std::tolower(l);});
        m_helpWords.push_back(helpWord);
    }
}


bool Help::activated(const Chess::Input::ParsedInput& parsedInput){
    if(parsedInput.size() != 1){
        return false;
    }
    auto lowerInput = parsedInput[0];
    std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), [](auto l){return std::tolower(l);});
    bool ok = std::any_of(m_helpWords.begin(), m_helpWords.end(), [&lowerInput](auto& helpWord){ return lowerInput == helpWord; });
    return ok;
}

bool Help::execute(Chess::Resources::GameResourcesInterface& gameResources){
    auto helpMessages = m_manager.helpTexts();
    for(const auto& helpMessage: helpMessages){
        if(!helpMessage.empty()){
            gameResources.printer().println(helpMessage);
        }
    }
    return true;
}

const std::string & Help::helpText() const{
    static const std::string empty = "";
    return empty;
}

}
}