#include "Output/UserInterface/VerySimpleMessageManager.hh"
namespace Chess{
namespace Output{
namespace UserInterface{

VerySimpleMessageManager::VerySimpleMessageManager(){
    m_messages[LanguageSelector::EN][MessageNameSelector::WELCOME_MESSAGE] = "Hi";
    m_messages[LanguageSelector::PT_BR][MessageNameSelector::WELCOME_MESSAGE] = "Oi";
}

const std::string& VerySimpleMessageManager::operator[](const MessageSelector& selector) const{
    auto language = selector.language;
    auto messageName = selector.messageName;

    if(m_messages.count(language) > 0){
        if(m_messages.at(language).count(messageName) > 0){
            return m_messages.at(language).at(messageName);
        }
    }
    return Chess::Output::UserInterface::ERROR_MESSAGE;
}

}
}
}