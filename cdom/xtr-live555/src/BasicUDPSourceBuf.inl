/** \copyright The MIT License */
#ifndef _RRDEMOCDOMLIVE555_BASICUDPSOURCEBUF_INL
#define _RRDEMOCDOMLIVE555_BASICUDPSOURCEBUF_INL

namespace rrdemo {
namespace cdom {
namespace live555 {

inline bool BasicUDPSource::Buf::empty() const
{
    return 0 == len_;
}

inline size_t BasicUDPSource::Buf::len() const
{
    return len_;
}

inline size_t BasicUDPSource::Buf::cpyf(const uint8_t *const src, const size_t len)
{
    auto actual = len < size ? len : size;  // min
    memcpy_s(data, size, src, actual);
    cur = 0;
    len_ = actual;
    return len - actual;
}

inline size_t BasicUDPSource::Buf::cpyt(uint8_t *const dst, const size_t siz, const size_t len) const
{
    assert(len <= len_);
    auto actual = len < siz ? len : siz;  // min
    memcpy_s(dst, siz, data, actual);
    return len - actual;
}

inline size_t BasicUDPSource::Buf::appf(const uint8_t *const src, const size_t len)
{
    auto free = size - len_;
    auto actual = len < free ? len : free;  // min
    memcpy_s(data + len_, free, src, actual);
    len_ += actual;
    return len - actual;
}

inline size_t BasicUDPSource::Buf::cutt(uint8_t *const dst, const size_t siz, const size_t len)
{
    assert(len <= len_);
    auto actual = len < siz ? len : siz;  // min
    memcpy_s(dst, siz, data + cur, actual);
    cur += actual;
    len_ -= actual;
    return len - actual;
}

inline void BasicUDPSource::Buf::clear()
{
    memset(data, 0, size);
    cur = 0;
    len_ = 0;
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_BASICUDPSOURCEBUF_INL
