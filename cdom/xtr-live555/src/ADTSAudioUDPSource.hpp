/** \file
 *  \author zhengrr
 *  \date 2017-1-3
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_ADTSAUDIOUDPSOURCE_HPP
#define _RRDEMOCDOMLIVE555_ADTSAUDIOUDPSOURCE_HPP

#include "BasicUDPSource.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

class ADTSAudioUDPSource : public BasicUDPSource {
public:
    /// 创建新的 ADTSAudioUDPSource 实例。
    static ADTSAudioUDPSource *createNew(UsageEnvironment &env, const u_int16_t port)
    {
        return new ADTSAudioUDPSource(env, port);  // leak
    }

protected:
    /// 构造函数。
    explicit ADTSAudioUDPSource(UsageEnvironment &env, const u_int16_t port) :
        BasicUDPSource(env, port)
    {}

    /// 析构函数。
    ~ADTSAudioUDPSource()
    {}

public:
    /// 已初始化。
    bool initialized() const;
    /// 采样率。
    unsigned sampfreq() const;
    /// 每帧时长（微秒）。
    unsigned usecspf() const;
    /// 通道数。
    unsigned channels() const;
    /// 特别配置。
    const char *configstr() const;

protected:
    char configstr_[5] {};

public:
    /// 重写的 initializeSourceBeforeEventLoop 函数，注入了辅助类的初始化。
    static void initializeSourceBeforeEventLoop(UsageEnvironment *env, u_int16_t port);

    /// 用户数据报协议包回调处理函数。
    /** param pck 包。
     *  param rcv 接收者地址。
     *  param snd 发送者地址。
     */
    void newpck(const PACKET &pck, const SOCKADDR_IN &rcv, const SOCKADDR_IN &snd) override;

    // 音频数据传输流帧头（Audio Data Transport Stream Frame Header）
    struct ADTSFH {
        /* Fixed Header */
        unsigned syncword : 12;                           // 同步码，固定为 FFF(16)；
        unsigned ID : 1;                                  // 固定为 0；
        unsigned layer : 2;                               // 固定为 0；
        unsigned protection_absent : 1;                   // 固定为 1；
        unsigned profile : 2;                             // 配置；
        unsigned sampling_frequency_index : 4;            // 采样率下标；
        unsigned privete_bit : 1;                         // 固定为 0；
        unsigned channel_configuration : 3;               // 声道配置；
        unsigned original_copy : 1;                       // 固定为 0；
        unsigned home : 1;                                // 固定为 0；
        /* Variable Header */
        unsigned copyright_identification_bit : 1;        // 固定为 0；
        unsigned copyright_identification_start : 1;      // 固定为 0；
        unsigned aac_frame_length : 13;                   // 全帧长度；
        unsigned adts_buffer_fullness : 11;               // 固定为 7FF(16)；
        unsigned number_of_raw_data_blocks_in_frame : 2;  // 固定为 0。
    } adtsfh;  //< 音频数据传输流头。
    static const unsigned SAMPLING_FREQUENCY_TABLE[16];     //< 采样率对应表。
    static const unsigned CHANNEL_CONFIGURATION_TABLE[16];  //< 声道配置对应表。

    // 音频数据传输流帧缓存（Audio Data Transport Stream Frame Buffer）
    struct ADTSFB {
        static const size_t SIZE {500000};  //< 百兆网 25FPS 最大尺寸。
        u_int8_t data[SIZE] {};
        size_t len {};
        int pcknum {};                      //< 缓存内含用户数据报协议包的数量。
    } adtsfb;

};// class ADTSAudioUDPSource

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_ADTSAUDIOUDPSOURCE_HPP
