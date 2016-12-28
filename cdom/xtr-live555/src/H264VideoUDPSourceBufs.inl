/** \copyright The MIT License */
#ifndef _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCEBUFS_INL
#define _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCEBUFS_INL

namespace rrdemo {
namespace cdom {
namespace live555 {

inline H264VideoUDPSource::Bufs::Bufs()
{
    for (auto &entity : entities)
        recycle(&entity);
}

inline size_t H264VideoUDPSource::Bufs::datalen() const
{
    return dataque.size();
}

inline size_t H264VideoUDPSource::Bufs::idlelen() const
{
    return idleque.size();
}

inline void H264VideoUDPSource::Bufs::push(Buf * const buf)
{
    mtx.lock(); {
        dataque.push(buf);
    } mtx.unlock();
}

inline H264VideoUDPSource::Buf* H264VideoUDPSource::Bufs::pop()
{
    Buf *buf;
    mtx.lock(); {
        if (dataque.empty()) {
            buf = nullptr;
        } else {
            buf = dataque.front();
            dataque.pop();
        }
    } mtx.unlock();
    return buf;
}

inline void H264VideoUDPSource::Bufs::recycle(Buf * const buf)
{
    buf->clear();
    mtx.lock(); {
        idleque.push(buf);
    } mtx.unlock();
}

inline H264VideoUDPSource::Buf* H264VideoUDPSource::Bufs::allocate()
{
    Buf *buf;
    mtx.lock(); {
        if (idleque.empty()) {
            buf = nullptr;
        } else {
            buf = idleque.front();
            idleque.pop();
        }
    } mtx.unlock();
    return buf;
}

inline H264VideoUDPSource::Buf* H264VideoUDPSource::Bufs::allocateforce()
{
    Buf *buf;
    mtx.lock(); {
        if (idleque.empty()) {
            if (dataque.empty()) {
                buf = nullptr;
            } else {
                buf = dataque.front();
                dataque.pop();
            }
        } else {
            buf = idleque.front();
            idleque.pop();
        }
    } mtx.unlock();
    if (nullptr != buf)
        buf->clear();
    return buf;
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCEBUFS_INL
