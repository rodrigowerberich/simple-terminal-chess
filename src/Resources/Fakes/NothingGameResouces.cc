#include "Resources/Fakes/NothingGameResources.hh"

namespace Chess{
namespace Resources{
namespace Fakes{

Chess::Input::ParserInterface& NothingGameResources::parser(){
    throw "Not Implemented";
}

Chess::Output::Printer& NothingGameResources::printer(){
    throw "Not Implemented";
}

const Chess::Output::UserInterface::LanguagePackageInterface& NothingGameResources::messageManager() const{
    throw "Not Implemented";
}

Chess::GameConfigurationInterface& NothingGameResources::configuration(){
    throw "Not Implemented";
}

}
}
}