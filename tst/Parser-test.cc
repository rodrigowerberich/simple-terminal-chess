#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "gtest/gtest.h"
#include "Parser.hh"


TEST(Parser, parseCorrectly) {
    Chess::Input::ParsedInput correctInput1 = {"Normal", "sentence", "12345[]a[d"};
    Chess::Input::ParsedInput correctInput2 = {"dhasdiashd;", "dsasdasd;", "s54das"};
    std::stringstream inputStream("Normal sentence 12345[]a[d\ndhasdiashd; dsasdasd; s54das");

    auto parser = Chess::Input::Parser(inputStream);

    auto input1 = parser.parse();
    auto input2 = parser.parse();

    ASSERT_TRUE(std::equal(input1.begin(), input1.end(), correctInput1.begin()));
    ASSERT_TRUE(std::equal(input2.begin(), input2.end(), correctInput2.begin()));
}