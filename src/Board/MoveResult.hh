#pragma once

#include <vector>

#include "Board/Position.hh"
#include "Board/PieceDescription.hh"

namespace Chess{
namespace Board{

class MoveResult{
public:
    enum class Status{
        Ok ,
        InvalidInput,
        NoMovement,
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
        struct NoMovement{

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
        Info::NoMovement noMovement;
        Info(Info::Ok inputOk) {ok = inputOk;}
        Info(Info::InvalidInput inputInvalidInput) {invalidInput = inputInvalidInput;}
        Info(Info::Collision inputCollision) {collision = inputCollision;}
        Info(Info::NoMovement inputNoMovement) {noMovement = inputNoMovement;}
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