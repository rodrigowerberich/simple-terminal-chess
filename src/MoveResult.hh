#pragma once

#include <vector>

#include "BoardPosition.hh"
#include "PieceDescription.hh"

namespace Chess{
namespace Board{

class MoveResult{
public:
    enum class Status{
        Ok ,
        InvalidInput,
        // NoMovement,
        Collision
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
        struct Collision{
            bool sameSide;
            bool differentSide;
            Chess::Board::PieceDescription originalPiece;
            Chess::Board::PieceDescription colidingPiece;
            Chess::Board::Position position;
        };
        Info::Ok ok;
        Info::InvalidInput invalidInput;
        Info::Collision collision;
        Info(Info::Ok inputOk) {ok = inputOk;}
        Info(Info::InvalidInput inputInvalidInput) {invalidInput = inputInvalidInput;}
        Info(Info::Collision inputCollision) {collision = inputCollision;}
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