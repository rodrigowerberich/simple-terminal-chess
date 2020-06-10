#include "Output/UserInterface/VerySimpleMessageManager.hh"
#include "Output/UserInterface/MessageSelector.hh"

namespace Chess{
namespace Output{
namespace UserInterface{

VerySimpleLanguagePackage::VerySimpleLanguagePackage(){
}

VerySimpleLanguagePackage::VerySimpleLanguagePackage(const LanguagePackFormat& languagePack):
    m_languagePack{languagePack}{
}
const std::string& VerySimpleLanguagePackage::operator[](const std::string& messageName) const{
    if(m_languagePack.count(messageName) > 0){
        return m_languagePack.at(messageName);
    }
    return Chess::Output::UserInterface::ERROR_MESSAGE;
}


VerySimpleMessageManager::VerySimpleMessageManager(){
    std::map<std::string, std::string> enLanguagePack;
    enLanguagePack[MessageNameSelector::WELCOME_MESSAGE] = "Hi";

    std::map<std::string, std::string> ptBrLanguagePack;
    ptBrLanguagePack[MessageNameSelector::WELCOME_MESSAGE] = "Oi";

    std::map<std::string, std::string> emptyLanguagePack;

    m_languagePacks[LanguageSelector::EN] = {enLanguagePack};
    m_languagePacks[LanguageSelector::PT_BR] = {ptBrLanguagePack};
    m_languagePacks[""] = {emptyLanguagePack};
}
const LanguagePackageInterface& VerySimpleMessageManager::operator[](const std::string& languageSelector) const{
    if(m_languagePacks.count(languageSelector) > 0){
        return m_languagePacks.at(languageSelector);
    }
    return m_languagePacks.at("");
}

}
}
}