#pragma once

#include "ParserInterface.hh"

namespace Chess{

class GameResources
{
private:
    Chess::Input::ParserInterface& m_parser;
public:
    GameResources(Chess::Input::ParserInterface& parser):
    m_parser{parser}{};
    ~GameResources(){};

    Chess::Input::ParserInterface& parser();
};

}