#include "Input/ParsedInput.hh"

std::ostream& operator<<(std::ostream& os, const Chess::Input::ParsedInput& input){
    os << input.originalInput();
    return os;
}
