#include "MoveResult.hh"

namespace Chess{
namespace Board{

MoveResult::MoveResult(MoveResult::Status status, MoveResult::Info info):
m_status{status},
m_info{info}{

}


MoveResult::Status MoveResult::status() const{
    return m_status;
}

template <>
const MoveResult::Info::Ok& MoveResult::info<MoveResult::Info::Ok>() const{
    return m_info.ok;
}

template <>
const MoveResult::Info::InvalidInput& MoveResult::info<MoveResult::Info::InvalidInput>() const{
    return m_info.invalidInput;
}


}
}