/** \file
 *  \author zhengrr
 *  \date 2017-1-4
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_FLVDEMUXH264VIDEOUDPSOURCE_HPP
#define _RRDEMOCDOMLIVE555_FLVDEMUXH264VIDEOUDPSOURCE_HPP

#include "H264VideoUDP/H264VideoUDPSource.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

class FLVDemuxH264VideoUDPSource : public H264VideoUDPSource {
public:
    /// 创建新的 H264VideoUDPSource 实例。
    static FLVDemuxH264VideoUDPSource *createNew(
        UsageEnvironment &env, const u_int16_t port)
    {
        return new FLVDemuxH264VideoUDPSource(env, port);
    }

protected:
    /// 构造函数。
    explicit FLVDemuxH264VideoUDPSource(UsageEnvironment &env, const u_int16_t port) :
        H264VideoUDPSource(env, port)
    {}

    /// 析构函数。
    ~FLVDemuxH264VideoUDPSource()
    {}

public:
    /// 用户数据报协议包回调处理函数。
    /** param pck 包。
     *  param rcv 接收者地址。
     *  param snd 发送者地址。
     */
    void newpck(const PACKET &pck, const SOCKADDR_IN &rcv, const SOCKADDR_IN &snd) override;

};// class FLVDemuxH264VideoUDPSource

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_FLVDEMUXH264VIDEOUDPSOURCE_HPP
