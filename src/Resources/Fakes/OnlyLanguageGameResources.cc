#include "Resources/Fakes/OnlyLanguageGameResources.hh"

namespace Chess{
namespace Resources{
namespace Fakes{

Chess::Input::ParserInterface& OnlyLanguageGameResources::parser(){
    throw "Not Implemented";
}

Chess::Output::Printer& OnlyLanguageGameResources::printer(){
    throw "Not Implemented";
}

const Chess::Output::UserInterface::LanguagePackageInterface& OnlyLanguageGameResources::messageManager() const{
    return m_messageManager[m_configuration.language()];
}

Chess::GameConfigurationInterface& OnlyLanguageGameResources::configuration(){
    return m_configuration;
}

}
}
}