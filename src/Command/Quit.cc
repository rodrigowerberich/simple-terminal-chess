#include "Command/Quit.hh"
#include "Output/UserInterface/MessageSelector.hh"

#include <algorithm>
#include <regex>
#include <iostream>

namespace Chess{
namespace Command{

Quit::Quit():
m_quitWords{"exit", "quit"}{
}


void Quit::init(Chess::Resources::GameResourcesInterface& gameResources){
    m_quitWords.clear();
    auto quitWordNames = gameResources.messageManager().filterHeaders([](const auto& messageName){
        return std::regex_match(messageName, std::regex("QUIT COMMAND QUIT WORD \\d*"));
    });
    for(const auto & quitWordName:quitWordNames){
        auto quitWord = gameResources.messageManager()[quitWordName];
        std::transform(quitWord.begin(), quitWord.end(), quitWord.begin(), [](auto l){return std::tolower(l);});
        std::cout << quitWord << std::endl;
        m_quitWords.push_back(quitWord);
    }
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

}
}