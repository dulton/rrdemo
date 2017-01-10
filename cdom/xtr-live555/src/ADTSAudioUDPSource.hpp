/** \file
 *  \author zhengrr
 *  \date 2017-1-3 – 5
 *  \copyright The MIT License
 */
#ifndef RRDEMO__CDOM__LIVE555__ADTS_AUDIO_UDP_SOURCE__HPP
#define RRDEMO__CDOM__LIVE555__ADTS_AUDIO_UDP_SOURCE__HPP

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
    const char *configstr();

protected:
    boolean initialized_ {false};
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

protected:
    /// 音频数据传输流帧头（Audio Data Transport Stream Frame Header）。
    /** 因端序和实现差异导致的不可移植性，位域结构体仅供按字段访问，勿按内存整体访问。
     */
    struct ADTSFH {
        /* Fixed Header */
        uint16_t syncword : 12;                          // 同步码，固定为 FFF(16)；
        uint8_t ID : 1;                                  // 固定为 0；
        uint8_t layer : 2;                               // 固定为 0；
        uint8_t protection_absent : 1;                   // 固定为 1；
        uint8_t profile : 2;                             // 配置；
        uint8_t sampling_frequency_index : 4;            // 采样率下标；
        uint8_t privete_bit : 1;                         // 固定为 0；
        uint8_t channel_configuration : 3;               // 声道配置；
        uint8_t original_copy : 1;                       // 固定为 0；
        uint8_t home : 1;                                // 固定为 0；
        /* Variable Header */
        uint8_t copyright_identification_bit : 1;        // 固定为 0；
        uint8_t copyright_identification_start : 1;      // 固定为 0；
        uint16_t aac_frame_length : 13;                  // 全帧长度；
        uint16_t adts_buffer_fullness : 11;              // 固定为 7FF(16)；
        uint8_t number_of_raw_data_blocks_in_frame : 2;  // 固定为 0。
    } adtsfh;  //< 音频数据传输流头。
    static const unsigned SAMPLING_FREQUENCY_TABLE[16];    //< 采样率对应表。
    static const unsigned CHANNEL_CONFIGURATION_TABLE[8];  //< 声道配置对应表。

    // 音频数据传输流帧缓存（Audio Data Transport Stream Frame Buffer）。
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

#endif// RRDEMO__CDOM__LIVE555__ADTS_AUDIO_UDP_SOURCE__HPP
