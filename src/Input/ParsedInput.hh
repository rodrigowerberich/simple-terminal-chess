#pragma once

#include <vector>
#include <string>

namespace Chess {
namespace Input{

// using ParsedInput = std::vector<std::string>;
class ParsedInput: public std::vector<std::string>{
private:
    std::string m_originalInput;
public:
    template <typename... T>
    ParsedInput(T&&... input):std::vector<std::string>{std::forward<T>(input)...},m_originalInput{""}{}
    void setOriginalInput(const std::string& originalInput){
        m_originalInput = originalInput;
    }
    const std::string& originalInput() const{
        return m_originalInput;
    }
};

}
}
std::ostream& operator<<(std::ostream& os, const Chess::Input::ParsedInput& input);
