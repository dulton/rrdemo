/** \copyright The MIT License */
#ifndef _RRDEMOCDOMLIVE555_BASICUDPSOURCEBUFS_INL
#define _RRDEMOCDOMLIVE555_BASICUDPSOURCEBUFS_INL

namespace rrdemo {
namespace cdom {
namespace live555 {

inline BasicUDPSource::Bufs::Bufs()
{
    for (auto &entity : entities)
        recycle(&entity);
}

inline size_t BasicUDPSource::Bufs::datalen() const
{
    return dataque.size();
}

inline size_t BasicUDPSource::Bufs::idlelen() const
{
    return idleque.size();
}

inline void BasicUDPSource::Bufs::push(Buf * const buf)
{
    mtx.lock(); {
        dataque.push(buf);
    } mtx.unlock();
}

inline BasicUDPSource::Buf* BasicUDPSource::Bufs::pop()
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

inline void BasicUDPSource::Bufs::recycle(Buf * const buf)
{
    buf->clear();
    mtx.lock(); {
        idleque.push(buf);
    } mtx.unlock();
}

inline BasicUDPSource::Buf* BasicUDPSource::Bufs::allocate()
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

inline BasicUDPSource::Buf* BasicUDPSource::Bufs::allocateforce()
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

#endif// _RRDEMOCDOMLIVE555_BASICUDPSOURCEBUFS_INL
