/** \file
 *  \author zhengrr
 *  \date 2017-1-4
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_FLVDEMUXADTSAUDIOUDPSOURCEHELPER_HPP
#define _RRDEMOCDOMLIVE555_FLVDEMUXADTSAUDIOUDPSOURCEHELPER_HPP

#include <map>

#include "FlvDemuxADTSAudioUDPSource.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

/// ADTSAudioUDPSource 辅助类，用于获取创建 RTP Sink 所需的信息。
/** 因 ADTS 源的特殊性，ADTS Server Media Subsession 需要在源初始化时便获取某些信息，
 *  而 UDP 源无法做到，因而使用此辅助类，在初始化之前获取指定信息，帮助主类初始化。
 */
class FLVDemuxADTSAudioUDPSourceHelper : public FLVDemuxADTSAudioUDPSource {
public:
    /// 分配辅助类。
    static bool allo(UsageEnvironment * const env, const u_int16_t port);
    /// 查找辅助类。
    static FLVDemuxADTSAudioUDPSourceHelper *find(const u_int16_t port);

protected:
    static std::map<u_int16_t, FLVDemuxADTSAudioUDPSourceHelper *> map;  //< 辅助类集实体。
    static std::mutex mtx;                                               //< 辅助类集锁。

public:
    /// 创建新的 FLVDemuxADTSAudioUDPSourceHelper 实例。
    static FLVDemuxADTSAudioUDPSourceHelper *createNew(UsageEnvironment &env, const u_int16_t port)
    {
        return new FLVDemuxADTSAudioUDPSourceHelper(env, port);
    }

protected:
    /// 构造函数。
    explicit FLVDemuxADTSAudioUDPSourceHelper(UsageEnvironment &env, const u_int16_t port) :
        FLVDemuxADTSAudioUDPSource(env, port)
    {}

    /// 析构函数。
    ~FLVDemuxADTSAudioUDPSourceHelper()
    {}

public:
    /// 用户数据报协议包回调处理函数。
    /** param pck 包。
     *  param rcv 接收者地址。
     *  param snd 发送者地址。
     */
    void newpck(const PACKET &pck, const SOCKADDR_IN &rcv, const SOCKADDR_IN &snd) override;

};// class FLVDemuxADTSAudioUDPSourceHelper 

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_FLVDEMUXADTSAUDIOUDPSOURCEHELPER_HPP
