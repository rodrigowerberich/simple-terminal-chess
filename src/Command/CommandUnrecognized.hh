// #pragma once

// #include <string>

// #include "CommandInterface.hh"

// namespace Chess{
// namespace Commands{

// class CommandUnrecognized: public Chess::Command::CommandInterface{
// private:
//     std::string m_unrecognizedCommandString;
// public:
//     void init(GameResources& gameResources) override;
//     bool activated(const Chess::Input::ParsedInput& parsedInput) override;
//     bool execute(GameResources& gameResources) override;
//     void setUnrecognizedString(const std::string& unrecognizedCommandString);
// };

// }
// }