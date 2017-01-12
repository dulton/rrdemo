/** \file
 *  \sa <http://download.macromedia.com/f4v/video_file_format_spec_v10_1.pdf>
 *  \author zhengrr
 *  \date 2017-1-4 – 11
 *  \copyright The MIT License
 */
#ifndef RRDEMO__CDOM__LIVE555__FLASH_VIDEO__HPP
#define RRDEMO__CDOM__LIVE555__FLASH_VIDEO__HPP

#include <cstdint>

#include "../../prj-clib/src/parse_bit_stream.h"

namespace rrdemo {
namespace cdom {
namespace live555 {

/// Flash Video Header。
/** 因端序和实现差异导致的不可移植性，位域结构体仅供按字段访问，勿按内存整体访问。
 */
struct FLVHeader {
    uint32_t signature : 24;          ///< 签名，固为 464C56(16) 'FLV'；
    uint8_t  version : 8;             ///< 版本；
    uint8_t  typeFlagsReserved5 : 5;  ///< 固为 0；
    uint8_t  typeFlagsAudio : 1;      ///< 音频标志位；
    uint8_t  typeFlagsReserved1 : 1;  ///< 固为 0；
    uint8_t  typeFlagsVideo : 1;      ///< 视频标志位；
    uint32_t dataOffset : 32;         ///< 文件体偏移量，通常为 9。
    uint8_t getVersion() const { return version; }
    bool haveAudio() const { return 0x1 == typeFlagsAudio; }
    bool haveVideo() const { return 0x1 == typeFlagsVideo; }
    uint32_t getOffset() const { return dataOffset; }
    static const size_t MINIMUM_SIZE {9u/*bytes*/};
    static bool Parse(FLVHeader &flvHeader, const uint8_t * const data, const size_t length);
    bool parse(const uint8_t * const data, const size_t length) { return Parse(*this, data, length); }
    static bool Validate(const uint8_t * const data, const size_t length) { FLVHeader tmp; return Parse(tmp, data, length); };
};

/// Flash Video Previous Tag Size。
struct FLVPreviousTagSize {
    uint32_t previousTagSize : 32;
    uint32_t getSize() const { return previousTagSize; }
    static const size_t SIZE {4u/*bytes*/};
    static bool Parse(FLVPreviousTagSize &flvPreviousTagSize, const uint8_t * const data, const size_t length);
    bool parse(const uint8_t * const data, const size_t length) { return Parse(*this, data, length); }
};

/// Flash Video Tag Header。
struct FLVTagHeader {
    uint8_t  tagType : 8;            ///< Tag 类型；
    uint32_t dataSize : 24;          ///< 数据区尺寸；
    uint32_t timestamp : 24;         ///< 时间戳；
    uint8_t  timestampExtended : 8;  ///< 时间戳扩展；
    uint32_t streamID : 24;          ///< 固为 0。
    bool isAudio() const { return 0x08u == tagType; }
    bool isVideo() const { return 0x09u == tagType; }
    bool isScript() const { return 0x12u == tagType; }
    uint32_t getDataSize() const { return dataSize; }
    uint32_t getTimestamp() const { return static_cast<uint32_t>(timestampExtended) << 24 | static_cast<uint32_t>(timestamp); }
    static const size_t SIZE {11u/*bytes*/};
    static bool Parse(FLVTagHeader &flvTagHeader, const uint8_t * const data, const size_t length);
    bool parse(const uint8_t * const data, const size_t length) { return Parse(*this, data, length); }
    static bool Validate(const uint8_t * const data, const size_t length) { FLVTagHeader tmp; return Parse(tmp, data, length); }
};

/// Flash Video Tag Data (Audio)。
struct FLVTagDataAudio {
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
struct FLVTagDataVideo {
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
struct FLVTagDataScript {
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

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// RRDEMO__CDOM__LIVE555__FLASH_VIDEO__HPP
