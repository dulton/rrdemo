/** \copyright The MIT License */
#include "NetworkAbstractLayerUnit.hpp"

#include "../../prj-clib/src/parse_bit_stream.h"

namespace rrdemo {
namespace cdom {
namespace cpp_library {

bool NetworkAbstractLayerUnit::
Validate(const uint8_t * const data, const size_t size)
{
    uint32_t tmp;  // start_codes
    if (zrr_parse32bits(&tmp, data, size, 0, 3 * 8) && 1 == tmp)
        return true;
    if (zrr_parse32bits(&tmp, data, size, 0, 4 * 8) && 1 == tmp)
        return true;
    return false;
}

}// namespace cpp_library
}// namespace cdom
}// namespace rrdemo
