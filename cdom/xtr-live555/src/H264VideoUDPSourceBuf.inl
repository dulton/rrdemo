/** \copyright The MIT License */
#ifndef _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCEBUF_INL
#define _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCEBUF_INL

namespace rrdemo {
namespace cdom {
namespace live555 {

inline bool H264VideoUDPSource::Buf::empty() const
{
    return 0 == len_;
}

inline size_t H264VideoUDPSource::Buf::len() const
{
    return len_;
}

inline size_t H264VideoUDPSource::Buf::cpyf(uint8_t *const src, const size_t len)
{
    auto actual = len < size ? len : size;
    memcpy_s(data, size, src, actual);
    cur = 0;
    len_ = actual;
    return len - actual;
}

inline size_t H264VideoUDPSource::Buf::cpyt(uint8_t *const dst, const size_t siz, const size_t len) const
{
    assert(len <= len_);
    auto actual = len < siz ? len : siz;
    memcpy_s(dst, siz, data, actual);
    return len - actual;
}

inline size_t H264VideoUDPSource::Buf::appf(uint8_t *const src, const size_t len)
{
    auto free = size - len_;
    auto actual = len < free ? len : free;
    memcpy_s(data + len_, free, src, actual);
    len_ += actual;
    return len - actual;
}

inline size_t H264VideoUDPSource::Buf::cutt(uint8_t *const dst, const size_t siz, const size_t len)
{
    assert(len <= len_);
    auto actual = len < siz ? len : siz;
    memcpy_s(dst, siz, data + cur, actual);
    cur += actual;
    len_ -= actual;
    return len - actual;
}


inline void H264VideoUDPSource::Buf::clear()
{
    memset(data, 0, size);
    cur = 0;
    len_ = 0;
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCEBUF_INL
