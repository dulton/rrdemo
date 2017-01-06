/** \file
 *  \author zhengrr
 *  \date 2017-1-4 – 6
 *  \copyright The MIT License
 */
#ifndef RRDEMO__CDOM__LIVE555__FLASH_VIDEO_DEMULTIPLEXER__HPP
#define RRDEMO__CDOM__LIVE555__FLASH_VIDEO_DEMULTIPLEXER__HPP

#include <cstdint>

namespace rrdemo {
namespace cdom {
namespace live555 {

class FlashVideoDemultiplexer {
public:
    /// Flash Video 头。
    /** 因端序和实现差异导致的不可移植性，位域结构体仅供按字段访问，勿按内存整体访问。
     */
    struct FlashVideoHeader {
        uint32_t Signature : 24;          //< 签名，固定为 464C56(16) "FLV"；
        uint8_t  Version : 8;             //< 版本；
        uint8_t  TypeFlagsReserved5 : 5;  //< 固定为 0；
        uint8_t  TypeFlagsAudio : 1;      //< 音频标志位；
        uint8_t  TypeFlagsReserved1 : 1;  //< 固定为 0；
        uint8_t  TypeFlagsVideo : 1;      //< 视频标志位；
        uint32_t DataOffset : 32;         //< 文件体偏移量，通常为 9。
    };

    /// Flash Video 体 Tag 头。
    struct FlashVideoBodyTagHeader {
        uint8_t  TagType : 8;            //< Tag 类型，音频为 8，视频为 9，脚本为 12(16)，其余保留；
        uint32_t DataSize : 24;          //< 数据区尺寸；
        uint32_t Timestamp : 24;         //< 时间戳；
        uint8_t  TimestampExtended : 8;  //< 时间戳扩展；
        uint32_t StreamID : 24;          //< 固定为 0。
    };

    /// Flash Video 体 Tag 数据。
    struct FlashVideoBodyTagData {
        union {
            struct {
                uint8_t         SoundFormat : 4;       //< 音频格式；
                uint8_t         SoundRate : 2;         //< 采样率；
                uint8_t         SoundSize : 1;         //< 采样尺寸；
                uint8_t         SoundType : 1;         //< 单声道或立体声。
                union {
                    struct {
                        uint8_t AACPacketType : 8;     //< AAC 包类型，头为 0，数据为 1。
                    } AACFormat;
                    uint8_t     OtherFormat : 8;
                };
            } AudioType;
            struct {
                uint8_t         FrameType : 4;         //< 帧类型；
                uint8_t         CodecID : 4;           //< 视频格式。
                union {
                    struct {
                        uint8_t AVCPacketType : 8;     //< AVC 包类型，头为 0，NALU 为 1，尾为 2；
                        int32_t CompositionTime : 24;  //< 合成时间。
                    } AVCCodec;
                    uint32_t    OtherType : 32;
                };
            } VudioType;
        };
    };

    /// Flash Video 体上一 Tag 尺寸。
    struct FlashVideoBodyPreviousTagSize {
        uint32_t PreviousTagSize : 32;  //< 上一 Tag 尺寸。
    };

    /// 检验输入数据是否符合 Flash Video Header。
    /** \param[in] data
     *  \param[in] len
     */
    static bool gIsFlashVideoHeader(const uint8_t * const data, const size_t len);

    /// 检验输入数据是否符合 Flash Video Body Tag Header。
    /** \param[in] data
     *  \param[in] len
     *  \param[in] maxDataSize 额外限制：最大数据区尺寸，用以更精确检验。
     */
    static bool gIsFlashVideoBodyTagHeader(const uint8_t * const data, const size_t len,
                                           const size_t maxDataSize = 0);

    /// 解析 Flash Video Header。
    /** \param[out]    flvh
     *  \param[in]     data
     *  \param[in,out] cur
     *  \param[in]     len
     */
    static bool gParseFlashVideoHeader(FlashVideoHeader &flvh,
                                       const uint8_t * const data, size_t &cur, const size_t len);

    /// 解析 Flash Video Body Previous Tag Size。
    /** \param[out]    flvbpts
     *  \param[in]     data
     *  \param[in,out] cur
     *  \param[in]     len
     */
    static bool gParseFLVBodyPreviousTagSize(FlashVideoBodyPreviousTagSize &flvbpts,
                                             const uint8_t * const data, size_t &cur, const size_t len);

    /// 解析 Flash Video Body Tag Header。
    /** \param[out]    flvbth
     *  \param[in]     data
     *  \param[in,out] cur
     *  \param[in]     len
     */
    static bool gParseFLVBodyTagHeader(FlashVideoBodyTagHeader &flvbth,
                                       const uint8_t * const data, size_t &cur, const size_t len);

    /// 解析 FLV Body Tag Data。
    /** \param[in]     flvbth
     *  \param[out]    flvbtd
     *  \param[in]     data
     *  \param[in,out] cur
     *  \param[in]     len
     *  \todo Script tag parse.
     */
    static bool gParseFLVBodyTagData(const FlashVideoBodyTagHeader &flvbth,
                                     FlashVideoBodyTagData &flvbtd,
                                     const uint8_t * const data, size_t &cur, const size_t len);

protected:
    /// FlashVideoHeader 的简写。
    using FLVH_ = FlashVideoHeader;
    /// FlashVideoBodyTagHeader 的简写。
    using FLVBTH_ = FlashVideoBodyTagHeader;
    /// FlashVideoBodyTagData 的简写。
    using FLVBTD_ = FlashVideoBodyTagData;
    /// FlashVideoBodyPreviousTagSize 的简写。
    using FLVBPTS_ = FlashVideoBodyPreviousTagSize;

};// class FlashVideoDemultiplexer

/// FlashVideoDemultiplexer 的简写。
using FLVDemux = FlashVideoDemultiplexer;

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// RRDEMO__CDOM__LIVE555__FLASH_VIDEO_DEMULTIPLEXER__HPP
