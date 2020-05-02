#pragma once

#include "BoardPosition.hh"

namespace Chess{
namespace Board{

class MoveResult{
public:
    enum class Status{
        Ok ,
        InvalidInput //,
        // ColisionSameSide
        // ColisionOtherSide
    };
    union Info{
        struct Ok{
            Chess::Board::Position oldPosition;
            Chess::Board::Position newPosition;
        };
        struct InvalidInput{
        };
        Info::Ok ok;
        Info(Info::Ok inputOk) {ok = inputOk;}
    };
    MoveResult(MoveResult::Status status, MoveResult::Info info);
    MoveResult::Status status() const;
    template <typename T>
    const T& info() const;
private:
    MoveResult::Status m_status;
    MoveResult::Info m_info;
};

}
}