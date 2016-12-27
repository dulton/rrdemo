/** \file
 *  \author zhengrr
 *  \date 2016-12-24 – 27
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCESPECIAL_HPP
#define _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCESPECIAL_HPP

#include <mutex>
#include <queue>

#include <live555/FramedSource.hh>
#include <live555/Groupsock.hh>

namespace rrdemo {
namespace cdom {
namespace live555 {

struct buf_t {
    u_int8_t *data;
    size_t size;
};

class H264VideoUdpSourceSpecial : public FramedSource {
public:
    /// 初始化（UDP）源。
    static void initializeSource(UsageEnvironment *env, u_int16_t port);
    std::queue<buf_t *> bufs;  //< 缓冲队列。
    std::mutex bufsmtx;        //< 缓冲队列锁。
    buf_t *buf {};             //< 当前缓冲。
    int bufcur {};             //< 当前缓冲游标。

    /** \param env
     *  \param skt  收流套接字。
     *  \param pfs  推荐帧尺寸（Preferred Frame Size）。
     *  \param ptpf 每针播放耗时（Play Time Per Frame）。
     */
    static H264VideoUdpSourceSpecial *createNew(
        UsageEnvironment &env, Groupsock *skt, unsigned pfs = 0, unsigned ptpf = 0);

protected:
    explicit H264VideoUdpSourceSpecial(
        UsageEnvironment &env, Groupsock *skt, unsigned pfs, unsigned ptpf);

    ~H264VideoUdpSourceSpecial();

private:
    void doGetNextFrame() override;

protected:
    Groupsock *skt;

};// H264VideoUdpSourceSpecial

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCESPECIAL_HPP
