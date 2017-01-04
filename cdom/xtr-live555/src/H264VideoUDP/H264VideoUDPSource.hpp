/** \file
 *  \author zhengrr
 *  \date 2016-12-22 – 2017-1-4
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

protected:
    /// H.264 网络抽象层单元头（Network Abstract Layer Unit Header）。
    /** 因端序和实现差异导致的不可移植性，位域结构体仅供按字段访问，勿按内存整体访问。
     */
    struct NALUH {
        union {
            uint32_t variation4bytes : 32;  //< 起始码 4 字节变种，固定为 00000001(16)；
            uint32_t variation3bytes : 24;  //< 起始码 3 字节变种，固定为 000001(16)。
        } start_codes;                   //< 起始码；
        uint8_t forbidden_zero_bit : 1;  //< 禁止位，固定为 0；
        uint8_t nal_ref_idc : 2;         //< 参考重要度；
        uint8_t nal_unit_type : 5;       //< 网络抽象层单元类型。
    };
    /// H.264 网络抽象层单元 辅助增强信息（Supplemental Enhancement Information），nal_unit_type = 6。
    struct NALUSEI {};
    /// H.264 网络抽象层单元 序列参数集（Sequence Parameter Set），nal_unit_type = 7。
    struct NALUSPS {
        uint8_t profile_idc : 8;
        uint8_t constraint_set0_flag : 1;
        uint8_t constraint_set1_flag : 1;
        uint8_t constraint_set2_flag : 1;
        uint8_t constraint_set3_flag : 1;
        uint8_t reserved_zero_4bits : 4;
        uint8_t level_idc : 8;
    };
    /// H.264 网络抽象层单元 图片参数集（Picture Parameter Set），nal_unit_type = 8。
    struct NALUPPS {};

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
