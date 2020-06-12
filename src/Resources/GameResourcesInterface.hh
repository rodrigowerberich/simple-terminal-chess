#pragma once

#include "Input/ParserInterface.hh"
#include "Output/Printer.hh"
#include "Output/UserInterface/MessageManagerInterface.hh"
#include "GameConfigurationInterface.hh"

namespace Chess{
namespace Resources{

class GameResourcesInterface{
public:
    virtual Chess::Input::ParserInterface& parser() = 0;
    virtual Chess::Output::Printer& printer() = 0;
    virtual const Chess::Output::UserInterface::LanguagePackageInterface& messageManager() const = 0;
    virtual Chess::GameConfigurationInterface& configuration() = 0;   
};

}
}