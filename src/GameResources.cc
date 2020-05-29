#include "GameResources.hh"

namespace Chess{

Chess::Input::ParserInterface& GameResources::parser(){
    return m_parser;
}

Chess::Output::Printer& GameResources::printer(){
    return m_printer;
}


}