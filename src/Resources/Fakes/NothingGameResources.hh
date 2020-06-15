#pragma once

#include "Resources/GameResourcesInterface.hh"

namespace Chess{
namespace Resources{
namespace Fakes{

class NothingGameResources: public GameResourcesInterface{
private:
public:
    NothingGameResources(){}
    
    ~NothingGameResources(){};

    Chess::Input::ParserInterface& parser() override;
    Chess::Output::Printer& printer() override;
    const Chess::Output::UserInterface::LanguagePackageInterface& messageManager() const override;
    Chess::GameConfigurationInterface& configuration() override;
};

}
}
}