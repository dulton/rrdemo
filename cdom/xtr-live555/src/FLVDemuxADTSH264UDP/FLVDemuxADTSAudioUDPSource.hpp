/** \file
 *  \author zhengrr
 *  \date 2017-1-4
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_FLVDEMUXADTSAUDIOUDPSOURCE_HPP
#define _RRDEMOCDOMLIVE555_FLVDEMUXADTSAUDIOUDPSOURCE_HPP

#include "ADTSAudioUDP/ADTSAudioUDPSource.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

class FLVDemuxADTSAudioUDPSource : public ADTSAudioUDPSource {
public:
    /// 创建新的 FLVDemuxADTSAudioUDPSource 实例。
    static FLVDemuxADTSAudioUDPSource *createNew(UsageEnvironment &env, const u_int16_t port)
    {
        return new FLVDemuxADTSAudioUDPSource(env, port);  // leak
    }

protected:
    /// 构造函数。
    explicit FLVDemuxADTSAudioUDPSource(UsageEnvironment &env, const u_int16_t port) :
        ADTSAudioUDPSource(env, port)
    {}

    /// 析构函数。
    ~FLVDemuxADTSAudioUDPSource()
    {}

public:
    /// 重写的 initializeSourceBeforeEventLoop 函数，注入了辅助类的初始化。
    static void initializeSourceBeforeEventLoop(UsageEnvironment *env, u_int16_t port);

    /// 用户数据报协议包回调处理函数。
    /** param pck 包。
     *  param rcv 接收者地址。
     *  param snd 发送者地址。
     */
    void newpck(const PACKET &pck, const SOCKADDR_IN &rcv, const SOCKADDR_IN &snd) override;

};// class FLVDemuxADTSAudioUDPSource

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_FLVDEMUXADTSAUDIOUDPSOURCE_HPP
