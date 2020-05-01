#include <string>
#include <sstream>
#include <array>
#include <vector>

#include "gtest/gtest.h"
#include "Printer.hh"

TEST(Printer, print){
    std::stringstream outputStream;
    auto printer = Chess::Output::Printer(outputStream);
    auto correctValue = "Ola1212.73Ola---adeus32324.5oi";

    printer.print("Ola");
    printer.print(12);
    printer.print(12.73);
    printer.print("Ola", "-", "--adeus",3);
    printer.print(23,24.5,"oi");
    
    ASSERT_EQ(outputStream.str(), correctValue);
}

TEST(Printer, println){
    std::stringstream outputStream;
    auto printer = Chess::Output::Printer(outputStream);
    auto correctValue = "Oi amigo\n18\n13.75\nOla---adeus3\n2215\n\n";

    printer.println("Oi amigo");
    printer.println(18);
    printer.println(13.75);
    printer.println("Ola", "-", "--adeus",3);
    printer.println(22, 15);
    printer.println();

    
    ASSERT_EQ(outputStream.str(), correctValue);
}

TEST(Printer, printVectorArray){
    std::stringstream outputStream;
    auto printer = Chess::Output::Printer(outputStream);
    auto correctValue = "{1, 2, 3, 4, 5, 6}\n{7, 5, 2}\n{{7, 5.1, 2}, {1.5, 9.6, 4.2}}\n{{7, 5, 2}, {6, 1, 0}, {-4, -6, 2}}\n{{Oi, Hi}, {Tchau, Bye}}\n";

    std::vector<int> vectorOfNumbers = {1, 2, 3, 4, 5, 6};
    std::array<int,3> arrayOfNumbers = {7, 5, 2};
    std::vector<std::vector<double>> vectorOfVectorOfNumbers = {{7.0, 5.1, 2.0},{1.5,9.6,4.2}};
    std::array<std::array<int,3>,3> arrayOfArrayOfNumbers = {7, 5, 2, 6, 1, 0, -4, -6, 2};
    std::vector<std::array<std::string,2>> vectorOfArrayOfStrings = {{"Oi", "Hi"},{"Tchau", "Bye"}};


    printer.println(vectorOfNumbers);    
    printer.println(arrayOfNumbers);    
    printer.println(vectorOfVectorOfNumbers);    
    printer.println(arrayOfArrayOfNumbers);    
    printer.println(vectorOfArrayOfStrings);    

    
    ASSERT_EQ(outputStream.str(), correctValue);
}