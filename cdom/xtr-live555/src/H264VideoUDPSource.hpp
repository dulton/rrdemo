/** \file
 *  \author zhengrr
 *  \date 2016-12-22 – 2017-1-3
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
    static H264VideoUDPSource *createNew(
        UsageEnvironment &env, const u_int16_t port)
    {
        return new H264VideoUDPSource(env, port);
    }

protected:
    /// 构造函数。
    explicit H264VideoUDPSource(UsageEnvironment &env, const u_int16_t port) :
        BasicUDPSource(env, port)
    {}

    /// 析构函数。
    ~H264VideoUDPSource()
    {}

public:
    /// 用户数据报协议包回调处理函数。
    /** param pck 包。
     *  param rcv 接收者地址。
     *  param snd 发送者地址。
     */
    void newpck(const PACKET &pck, const SOCKADDR_IN &rcv, const SOCKADDR_IN &snd) override;

    /// H.264 网络抽象层单元缓存（Network Abstraction Layer Unit Buffer）。
    struct NALUB {
        static const size_t SIZE {500000};  //< 百兆网 25FPS 最大尺寸。
        u_int8_t data[SIZE] {};
        size_t len {};
        int pcknum {};                      //< 缓存内含用户数据报协议包的数量。
    } nalub;  //< H.264 网络抽象层单元缓存。

};// class H264VideoUDPSource

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_H264VIDEOUDPSOURCE_HPP
