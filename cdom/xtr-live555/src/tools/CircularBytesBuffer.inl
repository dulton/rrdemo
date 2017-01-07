/** \copyright The MIT License */
#ifndef RRDEMO__CDOM__LIVE555__CIRCULAR_BYTES_BUFFER__INL
#define RRDEMO__CDOM__LIVE555__CIRCULAR_BYTES_BUFFER__INL

#include "CircularBytesBuffer.hpp"

#include <cassert>
#include <cmath>
#include <cstring>

namespace rrdemo {
namespace cdom {
namespace live555 {

inline CircularBytesBuffer::
CircularBytesBuffer(size_t bufferSize) :
SIZE {bufferSize}
{
    data = new uint8_t[SIZE];
}

inline CircularBytesBuffer::
~CircularBytesBuffer()
{
    delete[] data;
}

inline size_t CircularBytesBuffer::
getLoadLength() const
{
    return length;
}

inline size_t CircularBytesBuffer::
getIdleLength() const
{
    return SIZE - length;
}

inline size_t CircularBytesBuffer::
addDataFrom(const uint8_t * const src, const size_t srclen)
{
    const size_t actlen = fmin(srclen, getIdleLength());  // actual length

    if (haveInvertedPoint() || actlen <= SIZE - end_position) {
        memcpy_s(data + end_position, getIdleLength(), src, actlen);
        endPositionDash(actlen);
    } else {
        const auto hlflen = SIZE - end_position;          // half length
        memcpy_s(data + end_position, hlflen, src, hlflen);
        endPositionDash(hlflen);
        const auto othlen = actlen - hlflen;              // other half length
        memcpy_s(data + end_position, othlen, src + hlflen, othlen);
        endPositionDash(othlen);
    }

    return srclen - actlen;
}

inline size_t CircularBytesBuffer::
copyDataInto(uint8_t * const dst, const size_t dstsize, const size_t dstlen) const
{
    const size_t actlen = fmin(dstlen, dstsize);    // actual length
    assert(actlen <= getLoadLength());

    if (!haveInvertedPoint() || actlen <= SIZE - start_position) {
        memcpy_s(dst, dstsize, data + start_position, actlen);
    } else {
        const auto hlflen = SIZE - start_position;  // half length
        memcpy_s(dst, dstsize, data + start_position, hlflen);
        memcpy_s(dst + hlflen, dstsize - hlflen, data, actlen - hlflen);
    }

    return dstlen - actlen;
}

inline size_t CircularBytesBuffer::
discardData(const size_t len)
{
    const auto actlen = fmin(len, getLoadLength());  // actual length

    if (!haveInvertedPoint() || actlen <= SIZE - start_position) {
        startPositionDash(actlen);
    } else {
        const auto hlflen = SIZE - start_position;  // half length
        startPositionDash(hlflen);
        const auto othlen = actlen - hlflen;        // other half length
        startPositionDash(othlen);
    }

    return len - actlen;
}

inline size_t CircularBytesBuffer::
cutDataInto(uint8_t * const dst, const size_t dstsize, const size_t dstlen)
{
    const auto discarded = copyDataInto(dst, dstsize, dstlen);
    discardData(dstlen);
    return discarded;
}

inline void CircularBytesBuffer::
clearData()
{
    length = 0;
    start_position = 0;
    end_position = 0;
}

inline bool CircularBytesBuffer::
haveInvertedPoint() const
{
    return 0 < length && !(start_position < end_position);
}

inline void CircularBytesBuffer::
startPositionDash(const size_t len)
{
    assert(len <= getLoadLength());
    assert(len <= SIZE - start_position);
    length -= len;
    start_position += len;
    if (SIZE == start_position) start_position = 0;
}

inline void CircularBytesBuffer::
endPositionDash(const size_t len)
{
    assert(len <= getIdleLength());
    assert(len <= SIZE - end_position);
    length += len;
    end_position += len;
    if (SIZE == end_position) end_position = 0;
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// RRDEMO__CDOM__LIVE555__CIRCULAR_BYTES_BUFFER__INL
