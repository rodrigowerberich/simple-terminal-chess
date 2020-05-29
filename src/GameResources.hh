#pragma once

#include "Input/ParserInterface.hh"
#include "Output/Printer.hh"

namespace Chess{

class GameResources
{
private:
    Chess::Input::ParserInterface& m_parser;
    Chess::Output::Printer& m_printer;
public:
    GameResources(Chess::Input::ParserInterface& parser, Chess::Output::Printer& printer):
    m_parser{parser},
    m_printer{printer}{};
    ~GameResources(){};

    Chess::Input::ParserInterface& parser();
    Chess::Output::Printer& printer();
};

}