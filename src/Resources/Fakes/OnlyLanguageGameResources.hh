#pragma once

#include "Resources/GameResourcesInterface.hh"

namespace Chess{
namespace Resources{
namespace Fakes{

class OnlyLanguageGameResources: public GameResourcesInterface{
private:
    Chess::Output::UserInterface::MessageManagerInterface& m_messageManager;
    Chess::GameConfigurationInterface& m_configuration;
public:
    OnlyLanguageGameResources(Chess::Output::UserInterface::MessageManagerInterface& messageManager,
                              Chess::GameConfigurationInterface& configuration):
    m_messageManager{messageManager},
    m_configuration{configuration}{}
    
    ~OnlyLanguageGameResources(){};

    Chess::Input::ParserInterface& parser() override;
    Chess::Output::Printer& printer() override;
    const Chess::Output::UserInterface::LanguagePackageInterface& messageManager() const override;
    Chess::GameConfigurationInterface& configuration() override;
};

}
}
}