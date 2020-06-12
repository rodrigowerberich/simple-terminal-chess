#include "BasicGameConfiguration.hh"
#include "Output/UserInterface/MessageSelector.hh"

namespace Chess{

BasicGameConfiguration::BasicGameConfiguration():m_language{Chess::Output::UserInterface::LanguageSelector::EN}{
}


const std::string& BasicGameConfiguration::language() const{
    return m_language;
}

void BasicGameConfiguration::setLanguage(const std::string& language){
    m_language = language;
}


}
