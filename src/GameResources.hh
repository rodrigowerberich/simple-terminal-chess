#pragma once

#include "Input/ParserInterface.hh"
#include "Output/Printer.hh"
#include "Output/UserInterface/MessageManagerInterface.hh"
#include "GameConfigurationInterface.hh"

namespace Chess{

class GameResources
{
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

    Chess::Input::ParserInterface& parser();
    Chess::Output::Printer& printer();
    const Chess::Output::UserInterface::LanguagePackageInterface& messageManager() const;
    Chess::GameConfigurationInterface& configuration();
};

}