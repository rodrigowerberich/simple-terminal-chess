#pragma once

#include "Input/ParserInterface.hh"
#include "Output/Printer.hh"
#include "Output/UserInterface/MessageManagerInterface.hh"

namespace Chess{

class GameResources
{
private:
    Chess::Input::ParserInterface& m_parser;
    Chess::Output::Printer& m_printer;
    Chess::Output::UserInterface::MessageManagerInterface& m_messageManager;
public:
    GameResources(Chess::Input::ParserInterface& parser, Chess::Output::Printer& printer, Chess::Output::UserInterface::MessageManagerInterface& messageManager):
    m_parser{parser},
    m_printer{printer},
    m_messageManager{messageManager}{};
    ~GameResources(){};

    Chess::Input::ParserInterface& parser();
    Chess::Output::Printer& printer();
    Chess::Output::UserInterface::MessageManagerInterface& messageManager();

};

}