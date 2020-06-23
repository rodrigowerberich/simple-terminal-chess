#pragma once

#include "Resources/GameResourcesInterface.hh"

namespace Chess{
namespace Resources{
namespace Fakes{

class PrinterLanguageConfigurationGameResources: public GameResourcesInterface{
private:
    Chess::Output::Printer& m_printer;
    Chess::Output::UserInterface::MessageManagerInterface& m_messageManager;
    Chess::GameConfigurationInterface& m_configuration;
public:
    PrinterLanguageConfigurationGameResources(Chess::Output::Printer& printer, 
                  Chess::Output::UserInterface::MessageManagerInterface& messageManager,
                  Chess::GameConfigurationInterface& configuration):
    m_printer{printer},
    m_messageManager{messageManager},
    m_configuration{configuration}{};
    ~PrinterLanguageConfigurationGameResources(){};

    Chess::Input::ParserInterface& parser() override;
    Chess::Output::Printer& printer() override;
    const Chess::Output::UserInterface::LanguagePackageInterface& messageManager() const override;
    Chess::GameConfigurationInterface& configuration() override;
};

}
}
}