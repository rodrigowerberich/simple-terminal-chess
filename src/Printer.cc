#include "Printer.hh"
namespace Chess{
namespace Output{

Printer::Printer(std::ostream& ostream):
m_ostream{ostream}{

}
Printer::~Printer(){

}

void Printer::println(){
    print("\n");
}

}
}