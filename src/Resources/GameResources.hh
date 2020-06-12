#pragma once

#include "Resources/GameResourcesInterface.hh"

namespace Chess{
namespace Resources{

class GameResources: public GameResourcesInterface{
private:
    Chess::Input::ParserInterface& m_parser;
    Chess::Output::Printer& m_printer;
    Chess::Output::UserInterface::MessageManagerInterface& m_messageManager;
    Chess::GameConfigurationInterface& m_configuration;
public:
    GameResources(Chess::Input::ParserInterface& parser, 
                  Chess::Output::Printer& printer, 
                  Chess::Output::UserInterface::MessageManagerInterface& messageManager,
                  Chess::GameConfigurationInterface& configuration):
    m_parser{parser},
    m_printer{printer},
    m_messageManager{messageManager},
    m_configuration{configuration}{};
    ~GameResources(){};

    Chess::Input::ParserInterface& parser() override;
    Chess::Output::Printer& printer() override;
    const Chess::Output::UserInterface::LanguagePackageInterface& messageManager() const override;
    Chess::GameConfigurationInterface& configuration() override;
};

}
}