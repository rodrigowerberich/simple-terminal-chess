#include "GameResources.hh"

namespace Chess{

Chess::Input::ParserInterface& GameResources::parser(){
    return m_parser;
}

Chess::Output::Printer& GameResources::printer(){
    return m_printer;
}

const Chess::Output::UserInterface::LanguagePackageInterface& GameResources::messageManager() const{
    return m_messageManager[m_configuration.language()];
}

Chess::GameConfigurationInterface& GameResources::configuration(){
    return m_configuration;
}

}