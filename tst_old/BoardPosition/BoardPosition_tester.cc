#include <string>
#include <vector>
#include <iostream>

#include "BoardPosition.hh"

int main(){
    using namespace Chess;
    auto result = true;

    auto validColumnsString = std::vector<std::string>{"A","B","C","D","E","F","G","H"};
    auto validRowsString = std::vector<std::string>{"1","2","3","4","5","6","7","8"};
    auto validPositionsStrings = std::vector<std::string>();
    for(const auto& validColumn: validColumnsString){
        for(const auto& validRow: validRowsString){
            validPositionsStrings.push_back(validColumn+validRow);
        }
    }


    auto validColumns = std::vector<Board::Column>{ Board::Column::A,
                                                    Board::Column::B,
                                                    Board::Column::C,
                                                    Board::Column::D,
                                                    Board::Column::E,
                                                    Board::Column::F,
                                                    Board::Column::G,
                                                    Board::Column::H
                                                  };
    auto validRows = std::vector<Board::Row>{ 1,
                                              2,
                                              3,
                                              4,
                                              5,
                                              6,
                                              7,
                                              8
                                            };
    int counter=0;
    for(const auto& validColumn: validColumns){
        for(const auto& validRow: validRows){
            auto position = Board::Position{ validColumn, validRow };
            result &= (position.toString() == validPositionsStrings[counter]);
            result &= position.isValid();
            counter++;
        }
    }

    auto invalidPositions = std::vector<Board::Position>
                    {
                        {Board::Column::A, 0},
                        {Board::Column::A, -1},
                        {Board::Column::A, -999999},
                        {Board::Column::A, 9},
                        {Board::Column::A, 9999999},
                        {Board::Column::Invalid, 1},
                        {Board::Column::Invalid, -1}
                    };

    for(const auto& invalidPosition:invalidPositions){
        result &= !invalidPosition.isValid();
        result &= (invalidPosition.toString() == "Invalid");
    }

    if(result){
        std::cout << "BoardPosition is working as intended!\n";
    }else{
        std::cout << "BoardPosition has failed!\n";
    }
    
    return result;

}