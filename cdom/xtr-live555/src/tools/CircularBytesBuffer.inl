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
addDataFrom(const uint8_t *const src, const size_t srclen)
{
    const size_t actlen = fmin(srclen, getIdleLength());  // actual length

    if (haveInvertedPoint() || actlen <= SIZE - end_position) {
        memcpy_s(data + end_position, getIdleLength(), src, actlen);
        end_position = SIZE != end_position + actlen ? end_position + actlen : 0;
    } else {
        const auto firlen = SIZE - epos;            // first half length
        memcpy_s(data + epos, idlelen(), src, firlen);
        epos = SIZE != epos + firlen ? epos + firlen : 0;
        const auto seclen = actlen - firlen;        // second half length
        memcpy_s(data + epos, idlelen(), src + firlen, seclen);
        epos = SIZE != epos + seclen ? epos + seclen : 0;
    }

    if (spos == epos && 0 < actlen)
        full = true;

    return srclen - actlen;
}

inline size_t CircularBytesBuffer::
cutDataInto(uint8_t *const dst, const size_t dstsize, const size_t dstlen)
{
    assert(dstlen <= loadlen());

    const size_t actlen = fmin(dstlen, dstsize);  // actual length

    if (!inverted() || actlen <= SIZE - spos) {
        memcpy_s(dst, dstsize, data + spos, actlen);
        spos = SIZE != spos + actlen ? spos + actlen : 0;
    } else {
        const auto firlen = SIZE - spos;          // first half length
        memcpy_s(dst, dstsize, data + spos, firlen);
        spos = SIZE != spos + actlen ? spos + actlen : 0;
        const auto seclen = actlen - firlen;      // second half length
        memcpy_s(dst + firlen, dstsize - firlen, data + spos, seclen);
        spos = SIZE != spos + actlen ? spos + actlen : 0;
    }

    if (full && 0 < actlen)
        full = false;

    return dstlen - actlen;
}

inline size_t CircularBytesBuffer::
copyDataInto(uint8_t* const dst, const size_t dstsize, const size_t dstlen) const
{
    assert(dstlen <= loadlen());

    const size_t actlen = fmin(dstlen, dstsize);  // actual length

    auto tmp = spos;                              // temporary

    if (!inverted() || actlen <= SIZE - tmp) {
        memcpy_s(dst, dstsize, data + tmp, actlen);
    } else {
        const auto firlen = SIZE - tmp;           // first half length
        memcpy_s(dst, dstsize, data + tmp, firlen);
        tmp = SIZE != tmp + actlen ? tmp + actlen : 0;
        const auto seclen = actlen - firlen;      // second half length
        memcpy_s(dst + firlen, dstsize - firlen, data + tmp, seclen);
    }

    return dstlen - actlen;
}

inline size_t CircularBytesBuffer::
discardData(const size_t len)
{
    const auto actlen = fmin(len, loadlen());      // actual length

    if (!inverted() || actlen <= SIZE - spos) {
        spos = SIZE != spos + actlen ? spos + actlen : 0;
    } else {
        const auto firlen = SIZE - spos;          // first half length
        spos = SIZE != spos + actlen ? spos + actlen : 0;
        const auto seclen = actlen - firlen;      // second half length
        spos = SIZE != spos + actlen ? spos + actlen : 0;
    }

    if (full && 0 < actlen)
        full = false;

    return len - actlen;
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

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// RRDEMO__CDOM__LIVE555__CIRCULAR_BYTES_BUFFER__INL
