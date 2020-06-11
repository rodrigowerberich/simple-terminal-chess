#include "BasicGameConfiguration.hh"
#include "Output/UserInterface/MessageSelector.hh"

namespace Chess{

const std::string& BasicGameConfiguration::language() const{
    return Chess::Output::UserInterface::LanguageSelector::EN;
}

}
