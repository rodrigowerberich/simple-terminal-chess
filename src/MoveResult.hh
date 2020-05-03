#pragma once

#include "BoardPosition.hh"
#include "PieceDescription.hh"

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
            enum class Type{
                InvalidPieceSelector,
                InvalidPosition
            };
            InvalidInput::Type type;
            Chess::Board::PieceDescription invalidPieceDescription;
        };
        Info::Ok ok;
        Info::InvalidInput invalidInput;

        Info(Info::Ok inputOk) {ok = inputOk;}
        Info(Info::InvalidInput inputInvalidInput) {invalidInput = inputInvalidInput;}
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