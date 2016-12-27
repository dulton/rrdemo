/** \file
 *  \author zhengrr
 *  \date 2016-12-22 – 27
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCE_HPP
#define _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCE_HPP

#include <mutex>
#include <queue>
#include <thread>

#include <live555/FramedSource.hh>
#include <live555/Groupsock.hh>

namespace rrdemo {
namespace cdom {
namespace live555 {

#ifdef CODING

class H264VideoUdpSource : public FramedSource {
public:
    /** \param env
     *  \param skt  收流套接字。
     *  \param pfs  推荐帧尺寸（Preferred Frame Size）。
     *  \param ptpf 每针播放耗时（Play Time Per Frame）。
     */
    static H264VideoUdpSource *createNew(
        UsageEnvironment &env, Groupsock *skt, unsigned pfs = 0, unsigned ptpf = 0);

protected:
    explicit H264VideoUdpSource(
        UsageEnvironment &env, Groupsock *skt, unsigned pfs, unsigned ptpf);

    ~H264VideoUdpSource();

private:
    void doGetNextFrame() override;

protected:
    Port port;                       //< 收流端口。

    /// 缓冲类型。
    struct buf_t {
        uint8_t data[300000];
        size_t size;
    };

    std::queue<buf_t *> bufsque;     //< 缓冲队列。

    std::thread *sinkthr {nullptr};  //< 接收者线程（Sink Thread）。

    /// 接收者线程函数。
    void sinkthrfunc();

    bool sinkloop {false};           //< 接收者线程标志。

    std::mutex quemtx;               //< 缓冲队列锁。

};// H264VideoUdpSource

#endif// CODING

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCE_HPP
