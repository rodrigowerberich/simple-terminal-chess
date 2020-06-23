#include "Resources/Fakes/PrinterLanguageConfigurationGameResources.hh"

namespace Chess{
namespace Resources{
namespace Fakes{

Chess::Input::ParserInterface& PrinterLanguageConfigurationGameResources::parser(){
    throw "This is a fake, should not be used in production code, only tests";
}

Chess::Output::Printer& PrinterLanguageConfigurationGameResources::printer(){
    return m_printer;
}

const Chess::Output::UserInterface::LanguagePackageInterface& PrinterLanguageConfigurationGameResources::messageManager() const{
    return m_messageManager[m_configuration.language()];
}

Chess::GameConfigurationInterface& PrinterLanguageConfigurationGameResources::configuration(){
    return m_configuration;
}

}
}
}