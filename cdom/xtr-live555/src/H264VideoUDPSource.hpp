/** \file
 *  \author zhengrr
 *  \date 2016-12-22 – 30
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCE_HPP
#define _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCE_HPP

#include "BasicUDPSource.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

class H264VideoUDPSource : public BasicUDPSource {
public:
    /// 创建新的 H264VideoUDPSource 实例。
    /** \param env
     *  \param skt  收流套接字。
     *  \param pfs  推荐帧尺寸（Preferred Frame Size）。
     *  \param ptpf 每针播放耗时（Play Time Per Frame）。
     */
    static H264VideoUDPSource *createNew(
        UsageEnvironment &env, Groupsock *skt, unsigned pfs = 0, unsigned ptpf = 0)
    {
        return new H264VideoUDPSource(env, skt, pfs, ptpf);
    }

protected:
    /// 构造函数。
    explicit H264VideoUDPSource(UsageEnvironment &env, Groupsock *skt, unsigned, unsigned) :
        BasicUDPSource(env, skt)
    {}

    /// 析构函数。
    ~H264VideoUDPSource()
    {}

public:
    /// 用户数据报协议包回调处理函数。
    /** param PCKS 尺寸（内存）。
     *  param pck  数据。
     *  param pckl 长度（数据）。
     */
    void newpck(const size_t PCKS, const uint8_t * const pck, const size_t pckl) override;

    // H.264 网络抽象层单元缓存（Network Abstraction Layer Unit Buffer）
    static const size_t NALUBS {500000};  //< NALUB Size。百兆网25FPS最大尺寸。
    u_int8_t nalub[NALUBS] {};            //< NALUB。
    size_t nalubl {};                     //< NALUB Length。
    int nalufc {};                        //< NALU Flag Check。

};// H264VideoUdpSource

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCE_HPP
