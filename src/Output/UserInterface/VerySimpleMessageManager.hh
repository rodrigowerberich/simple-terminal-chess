# pragma once

#include "Output/UserInterface/MessageManagerInterface.hh"

#include <map>

namespace Chess{
namespace Output{
namespace UserInterface{

class VerySimpleLanguagePackage: public LanguagePackageInterface{
private:
    using LanguagePackFormat = std::map<std::string, std::string>;
    LanguagePackFormat m_languagePack;
public:
    VerySimpleLanguagePackage();
    VerySimpleLanguagePackage(const LanguagePackFormat& languagePack);
    const std::string& operator[](const std::string& messageSelector) const override;
    const std::vector<std::string> filterHeaders(const FilterFunction&) const override;
};

class VerySimpleMessageManager: public MessageManagerInterface{
private:
    std::map<std::string, VerySimpleLanguagePackage> m_languagePacks;
public:
    VerySimpleMessageManager();
    const LanguagePackageInterface& operator[](const std::string& languageSelector) const override;
};

}
}
}