#pragma once

#include <ostream>
#include <vector>
#include <array>
#include <map>


namespace Chess{
namespace Output{

class Printer
{
private:
    std::ostream& m_ostream;
public:
    Printer(std::ostream& ostream);
    ~Printer();
    template <typename T>
    void print(const T& toPrint);
    template <typename T, typename... Args>
    void print(const T& toPrint, const Args&... args);
    template <typename T>
    void print(const std::vector<T> & toPrint);
    template <typename T, std::size_t N>
    void print(const std::array<T,N> & toPrint);
    void println();
    template <typename T>
    void println(const T& toPrint);
    template <typename T, typename... Args>
    void println(const T& toPrint, const Args&... args);
};

template <typename T>
void Printer::print(const T& toPrint){
    m_ostream << toPrint;
}

template <typename T, typename... Args>
void Printer::print(const T& toPrint, const Args&... args){
    print(toPrint);
    print(args...);
}

template <typename T>
void Printer::print(const std::vector<T> & toPrint){
    auto size = toPrint.size();
    unsigned i = 0;
    print("{");
    for(const auto& value:toPrint){
        print(value);
        i++;
        if(i < size){
            print(", ");
        }
    }
    print("}");
}

template <typename T, std::size_t N>
void Printer::print(const std::array<T,N> & toPrint){
    auto size = N;
    unsigned i = 0;
    print("{");
    for(const auto& value:toPrint){
        print(value);
        i++;
        if(i < size){
            print(", ");
        }
    }
    print("}");

}


template <typename T>
void Printer::println(const T& toPrint){
    print(toPrint);
    print("\n");
}

template <typename T, typename... Args>
void Printer::println(const T& toPrint, const Args&... args){
    print(toPrint, args...);
    print("\n");
}

}
}