#include "Output/UserInterface/VerySimpleMessageManager.hh"
#include "Output/UserInterface/MessageSelector.hh"

namespace Chess{
namespace Output{
namespace UserInterface{

VerySimpleLanguagePackage::VerySimpleLanguagePackage(){
}

VerySimpleLanguagePackage::VerySimpleLanguagePackage(const LanguagePackFormat& languagePack):
    m_languagePack{languagePack}{
}
const std::string& VerySimpleLanguagePackage::operator[](const std::string& messageName) const{
    if(m_languagePack.count(messageName) > 0){
        return m_languagePack.at(messageName);
    }
    return Chess::Output::UserInterface::ERROR_MESSAGE;
}

const std::vector<std::string> VerySimpleLanguagePackage::filterHeaders(const FilterFunction& filter) const{
    std::vector<std::string> result;
    for(const auto& pair:m_languagePack){
        if(filter(pair.first)){
            result.push_back(pair.first);
        }
    }
    return result;
}


VerySimpleMessageManager::VerySimpleMessageManager(){
    std::map<std::string, std::string> enLanguagePack;
    enLanguagePack[MessageSelector::WELCOME_MESSAGE] = "Hi";
    enLanguagePack[MessageSelector::GAME_START_WELCOME_MESSAGE] = "Welcome to Terminal Chess!!";

    enLanguagePack[MessageSelector::QUIT_COMMAND_QUIT_WORD_1] = "exit";
    enLanguagePack[MessageSelector::QUIT_COMMAND_QUIT_WORD_2] = "quit";
    enLanguagePack[MessageSelector::QUIT_COMMAND_HELP_BEFORE_MESSAGE] = "To close the program type any of the following: ";
    enLanguagePack[MessageSelector::QUIT_COMMAND_HELP_AFTER_MESSAGE] = ".";

    enLanguagePack[MessageSelector::BEFORE_UNRECOGNIZED_INPUT_MESSAGE] = "The command";
    enLanguagePack[MessageSelector::AFTER_UNRECOGNIZED_INPUT_MESSAGE] = "is not recognized";

    enLanguagePack[MessageSelector::HELP_COMMAND_HELP_WORD_1] = "help";

    std::map<std::string, std::string> ptBrLanguagePack;
    ptBrLanguagePack[MessageSelector::WELCOME_MESSAGE] = "Oi";
    ptBrLanguagePack[MessageSelector::GAME_START_WELCOME_MESSAGE] = "Bem vindo ao Xadrez no terminal!!";

    ptBrLanguagePack[MessageSelector::QUIT_COMMAND_QUIT_WORD_1] = "sair";
    ptBrLanguagePack[MessageSelector::QUIT_COMMAND_QUIT_WORD_2] = "finalizar";
    ptBrLanguagePack["QUIT COMMAND QUIT WORD 3"] = "terminar";
    ptBrLanguagePack[MessageSelector::QUIT_COMMAND_HELP_BEFORE_MESSAGE] = "Para sair do programa basta digitar um dos comandos listados a seguir";
    ptBrLanguagePack[MessageSelector::QUIT_COMMAND_HELP_AFTER_MESSAGE] = ".";

    ptBrLanguagePack[MessageSelector::BEFORE_UNRECOGNIZED_INPUT_MESSAGE] = "O comando";
    ptBrLanguagePack[MessageSelector::AFTER_UNRECOGNIZED_INPUT_MESSAGE] = "não é reconhecido";

    ptBrLanguagePack[MessageSelector::HELP_COMMAND_HELP_WORD_1] = "ajuda";

    std::map<std::string, std::string> emptyLanguagePack;

    m_languagePacks[LanguageSelector::EN] = {enLanguagePack};
    m_languagePacks[LanguageSelector::PT_BR] = {ptBrLanguagePack};
    m_languagePacks[""] = {emptyLanguagePack};
}
const LanguagePackageInterface& VerySimpleMessageManager::operator[](const std::string& languageSelector) const{
    if(m_languagePacks.count(languageSelector) > 0){
        return m_languagePacks.at(languageSelector);
    }
    return m_languagePacks.at("");
}

}
}
}