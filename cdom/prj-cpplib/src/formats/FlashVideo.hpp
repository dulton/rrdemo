/** \file
 *  \brief Flash 视频（FLV、F4V，Flash Video）格式。
 *  \sa [Adobe Flash Video File Format Specification Version 10.1](
 *          http://download.macromedia.com/f4v/video_file_format_spec_v10_1.pdf)
 *  \author zhengrr
 *  \date 2017-1-4 – 13
 *  \copyright The MIT License
 */
#ifndef RRDEMO__CDOM__CPP_LIBRARY__FLASH_VIDEO__HPP
#define RRDEMO__CDOM__CPP_LIBRARY__FLASH_VIDEO__HPP

#include <cstdint>

#include "api.hpp"

namespace rrdemo {
namespace cdom {
namespace cpp_library {

struct RRDEMO__CDOM__CPP_LIBRARY__API FLVTag {
    /* Tag Header */
    uint8_t  reserved2 : 2;          ///< 保留位，恒为 0；
    uint8_t  filter : 1;             ///< 预处理标志位；
    uint8_t  tagType : 5;            ///< Tag 类型；
    uint32_t dataSize : 24;          ///< 数据区尺寸；
    uint32_t timestamp : 24;         ///< 时间戳；
    uint8_t  timestampExtended : 8;  ///< 时间戳扩展；
    uint32_t streamID : 24;          ///< 恒为 0。
    /* Tag Data */

    /* Tag Size */
    uint32_t previousTagSize : 32;   ///< 后置尺寸。

    bool isAudio() const { return 0x08 == tagType; }
    bool isVideo() const { return 0x09 == tagType; }
    bool isScript() const { return 0x12 == tagType; }
    uint32_t getDataSize() const { return dataSize; }
    uint32_t getTimestamp() const { return static_cast<uint32_t>(timestampExtended) << 24 | static_cast<uint32_t>(timestamp); }

    /// 检验数据是否符合格式。
    static bool Validate(const uint8_t * const data, const size_t size);

    /// 解析数据。
    bool parse(const uint8_t * const data, const size_t size);

};// struct FLVTag

struct RRDEMO__CDOM__CPP_LIBRARY__API FLV {
    /* Header */
    uint32_t signature : 24;          ///< 签名，恒为 'F'(0x46) 'L'(0x4C) 'V'(0x56)；
    uint8_t  version : 8;             ///< 版本号；
    uint8_t  typeFlagsReserved5 : 5;  ///< 保留位，恒为 0；
    uint8_t  typeFlagsAudio : 1;      ///< 音频标志位；
    uint8_t  typeFlagsReserved1 : 1;  ///< 保留位，恒为 0；
    uint8_t  typeFlagsVideo : 1;      ///< 视频标志位；
    uint32_t dataOffset : 32;         ///< 数据偏移量，通常为 9。
    /* Header Size */
    uint32_t previousTagSize0 : 32;   ///< 头的后置尺寸，恒为 0。
    /* Tags */
    FLVTag *tags {};

    uint8_t getVersion() const { return version; }
    bool hasAudio() const { return 1 == typeFlagsAudio; }
    bool hasVideo() const { return 1 == typeFlagsVideo; }
    uint32_t getOffset() const { return dataOffset; }

    /// 检验数据是否符合格式。
    static bool Validate(const uint8_t * const data, const size_t size);

    /// 解析数据。
    bool parse(const uint8_t * const data, const size_t size);

};// struct FLV

/// Flash Video Tag Data (Audio)。
struct RRDEMO__CDOM__CPP_LIBRARY__API FLVTagDataAudio {
    uint8_t soundFormat : 4;  ///< 音频格式；
    uint8_t soundRate : 2;    ///< 采样率；
    uint8_t soundSize : 1;    ///< 采样尺寸；
    uint8_t soundType : 1;    ///< 单声道或立体声。
    union {
        struct {
            uint8_t aacPacketType : 8;  ///< AAC 包类型。
            uint8_t *data;
        } aacFormat;
        uint8_t *soundData;
    };
    bool isLinearPCMPlatformEndian() const { return 0x0u == soundFormat; }
    bool isADPCM() const { return 0x1u == soundFormat; }
    bool isMP3() const { return 0x2u == soundFormat; }
    bool isLinearPCMLittleEndian() const { return 0x3u == soundFormat; }
    bool isNellymoser16kHzMono() const { return 0x4u == soundFormat; }
    bool isNellymoser8kHzMono() const { return 0x5u == soundFormat; }
    bool isNellymoser() const { return 0x6u == soundFormat; }
    bool isG711AlawLogarithmicPCM() const { return 0x7u == soundFormat; }
    bool isG711mulawLogarithmicPCM() const { return 0x8u == soundFormat; }
    bool isAAC() const { return 0xAu == soundFormat; }
    bool isSpeex() const { return 0xBu == soundFormat; }
    bool isMP38kHz() const { return 0xEu == soundFormat; }
    bool isDeviceSpecificSound() const { return 0xFu == soundFormat; }
    bool is5d5kHz() const { return 0x0u == soundRate; }
    bool is11kHz() const { return 0x1u == soundRate; }
    bool is22kHz() const { return 0x2u == soundRate; }
    bool is44kHz() const { return 0x3u == soundRate; }
    bool isSnd8Bit() const { return 0x0u == soundSize; }
    bool isSnd16Bit() const { return 0x1u == soundSize; }
    bool isSndMono() const { return 0x0u == soundType; }
    bool isSndStereo() const { return 0x1u == soundType; }
    bool isAACSequenceHeader() const { return isAAC() && 0x0u == aacFormat.aacPacketType; }
    bool isAACRaw() const { return isAAC() && 0x1u == aacFormat.aacPacketType; }
    size_t getDataOffset() const { return isAAC() ? 2u : 1u; }
    static const size_t MINIMUM_SIZE {1u/*bytes*/};
    static bool Parse(FLVTagDataAudio &flvTagData, const uint8_t * const data, const size_t length);
    bool parse(const uint8_t * const data, const size_t length) { return Parse(*this, data, length); }
};

/// Flash Video Tag Data (Video)。
struct RRDEMO__CDOM__CPP_LIBRARY__API FLVTagDataVideo {
    uint8_t frameType : 4;  ///< 帧类型；
    uint8_t codecID : 4;    ///< 视频格式。
    union {
        struct {
            uint8_t avcPacketType : 8;     ///< AVC 包类型；
            int32_t compositionTime : 24;  ///< 合成时间。
            uint8_t *data;
        } avcCodec;
        uint8_t *videoData;
    };
    bool isKeyframe() const { return 0x1u == frameType; }
    bool isInterFrame() const { return 0x2u == frameType; }
    bool isDisposableInterFrame() const { return 0x3u == frameType; }
    bool isGeneratedKeyframe() const { return 0x4u == frameType; }
    bool isVideoInfoCommandFrame() const { return 0x5u == frameType; }
    bool isJPEG() const { return 0x1u == codecID; }
    bool isSorensonH263() const { return 0x2u == codecID; }
    bool isScreenVideo() const { return 0x3u == codecID; }
    bool isOn2VP6() const { return 0x4u == codecID; }
    bool isOn2VP6WithAlphaChannel() const { return 0x5u == codecID; }
    bool isScreenVideoVersion2() const { return 0x6u == codecID; }
    bool isAVC() const { return 0x7u == codecID; }
    bool isAVCSequenceHeader() const { return isAVC() && 0x0u == avcCodec.avcPacketType; }
    bool isAVCNALU() const { return isAVC() && 0x1u == avcCodec.avcPacketType; }
    bool isAVCEndOfSequence() const { return isAVC() && 0x2u == avcCodec.avcPacketType; }
    int32_t getCompositionTime() const { return isAVCNALU() ? avcCodec.compositionTime : 0; }
    size_t getDataOffset() const { return isAVC() ? 5u : 1u; }
    static const size_t MINIMUM_SIZE {1/*bytes*/};
    static bool Parse(FLVTagDataVideo &flvTagData, const uint8_t * const data, const size_t length);
    bool parse(const uint8_t * const data, const size_t length) { return Parse(*this, data, length); }
};

/// Flash Video Tag Data (Script)。
struct RRDEMO__CDOM__CPP_LIBRARY__API FLVTagDataScript {
    struct Object {
        struct {
            uint16_t length : 16;
            uint8_t *data;
        } name;
        struct {
            uint8_t type : 8;
            union {} value;
        } data;
    } *objects;
    uint32_t end : 32;
    static const size_t MINIMUM_SIZE {4u/*bytes*/};
};

}// namespace cpp_library
}// namespace cdom
}// namespace rrdemo

#endif// RRDEMO__CDOM__CPP_LIBRARY__FLASH_VIDEO__HPP
