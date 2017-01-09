/** \copyright The MIT License */
#include "H264NetworkAbstractLayerUnit.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

bool H264NetworkAbstractLayerUnit::IsHeader(const uint8_t * const data, const size_t length)
{
    if (0x00u == data[0] && 0x00u == data[1] && 0x00u == data[2] && 0x01u == data[3])
        return true;
    if (0x00u == data[0] && 0x00u == data[1] && 0x01u == data[2])
        return true;
    return false;
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
