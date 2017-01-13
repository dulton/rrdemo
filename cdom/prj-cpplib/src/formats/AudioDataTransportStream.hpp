/** \file
 *  \brief 音频数据传输流（ADTS，Audio Data Transport Stream）格式。
 *  \sa [ISO/IEC 13818-7:2006(en)](
 *          http://iso.org/obp/ui/#iso:std:iso-iec:13818:-7:ed-4:v1:en)
 *  \author zhengrr
 *  \date 2017-1-3 – 13
 *  \copyright The MIT License
 */
#ifndef RRDEMO__CDOM__CPP_LIBRARY__AUDIO_DATA_TRANSPORT_STREAM__HPP
#define RRDEMO__CDOM__CPP_LIBRARY__AUDIO_DATA_TRANSPORT_STREAM__HPP

#include <cstdint>

namespace rrdemo {
namespace cdom {
namespace cpp_library {

/// 音频数据传输流帧头。
/** 因端序和实现差异导致的不可移植性，位域结构体仅供按字段访问，勿按内存整体访问。
 */
struct ADTSFHeader {
    /* Fixed Header */
    uint16_t syncword : 12;                          ///< 同步码，固为 FFF(16)；
    uint8_t ID : 1;                                  ///< 固为 0；
    uint8_t layer : 2;                               ///< 固为 0；
    uint8_t protection_absent : 1;                   ///< 固为 1；
    uint8_t profile : 2;                             ///< 配置；
    uint8_t sampling_frequency_index : 4;            ///< 采样率下标；
    uint8_t privete_bit : 1;                         ///< 固为 0；
    uint8_t channel_configuration : 3;               ///< 声道配置；
    uint8_t original_copy : 1;                       ///< 固为 0；
    uint8_t home : 1;                                ///< 固为 0；
    /* Variable Header */
    uint8_t copyright_identification_bit : 1;        ///< 固为 0；
    uint8_t copyright_identification_start : 1;      ///< 固为 0；
    uint16_t aac_frame_length : 13;                  ///< 全帧长度；
    uint16_t adts_buffer_fullness : 11;              ///< 固为 7FF(16)；
    uint8_t number_of_raw_data_blocks_in_frame : 2;  ///< 固为 0。
};

/// 音频数据传输流帧。
struct AudioDataTransportStreamFrame {
    static const size_t HEADER_SIZE;                       ///< ADTSF Header 尺寸；

    static const unsigned SAMPLING_FREQUENCY_TABLE[16];    ///< 采样率对应表；
    static const unsigned CHANNEL_CONFIGURATION_TABLE[8];  ///< 声道配置对应表。

    /// 检查输入数据是否符合 ADTSF Header。
    static bool IsHeader(const uint8_t * const data, const size_t length);

    /// 解析 ADTSF Header。
    static bool ParseHeader(
        ADTSFHeader &adtsfHeader, const uint8_t * const data, const size_t length);

};

}// namespace cpp_library
}// namespace cdom
}// namespace rrdemo

#endif// RRDEMO__CDOM__CPP_LIBRARY__AUDIO_DATA_TRANSPORT_STREAM__HPP
