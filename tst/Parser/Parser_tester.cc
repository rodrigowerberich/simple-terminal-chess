#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "Parser.hh"

int main(){
    auto phrase = "Normal sentence 12345[]a[d\ndhasdiashd; dsasdasd; s54das";
    Chess::Input::ParsedInput correctInput1 = {"Normal", "sentence", "12345[]a[d"};
    Chess::Input::ParsedInput correctInput2 = {"dhasdiashd;", "dsasdasd;", "s54das"};

    std::stringstream phaseStream(phrase);
    auto parser = Chess::Input::Parser(phaseStream);

    auto input1 = parser.parse();
    auto input2 = parser.parse();

    auto result1 = std::equal(input1.begin(), input1.end(), correctInput1.begin());
    auto result2 = std::equal(input2.begin(), input2.end(), correctInput2.begin());
    auto result = result1 && result2;

    if(result){
        std::cout << "Parser is working as intended!\n";
    }else{
        std::cout << "Parser is failed!\n";
    }
    
    return result;
}