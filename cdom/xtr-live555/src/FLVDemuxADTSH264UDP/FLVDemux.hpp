/** \file
 *  \author zhengrr
 *  \date 2017-1-4 – 5
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_FLVDEMUX_HPP
#define _RRDEMOCDOMLIVE555_FLVDEMUX_HPP

#include <cstdint>

namespace rrdemo {
namespace cdom {
namespace live555 {

class FLVDemux {
public:
    /// FLV 文件头（FLV Header）。
    /** 因端序和实现差异导致的不可移植性，位域结构体仅供按字段访问，勿按内存整体访问。
     */
    struct FLVH {
        uint32_t Signature : 24;         //< 签名，固定为 464C56(16) "FLV"；
        uint8_t Version : 8;             //< 版本；
        uint8_t TypeFlagsReserved5 : 5;  //< 固定为 0；
        uint8_t TypeFlagsAudio : 1;      //< 音频标志位；
        uint8_t TypeFlagsReserved1 : 1;  //< 固定为 0；
        uint8_t TypeFlagsVideo : 1;      //< 视频标志位；
        uint32_t DataOffset : 32;        //< 文件体偏移量，通常为 9。
    };
    /// FLV 文件体 Tag 头（FLV Body Tag Header）。
    struct FLVBTH {
        uint8_t TagType : 8;            //< Tag 类型，音频为 8，视频为 9，脚本为 12(16)，其余保留；
        uint32_t DataSize : 24;         //< 数据区尺寸；
        uint32_t Timestamp : 24;        //< 时间戳；
        uint8_t TimestampExtended : 8;  //< 时间戳扩展；
        uint32_t StreamID : 24;         //< 固定为 0。
    };
    /// FLV 文件体 Tag 数据（FLV Body Tag Data）。
    struct FLVBTD {
        union {
            struct {
                uint8_t SoundFormat : 4;  //< 音频格式；
                uint8_t SoundRate : 2;    //< 采样率；
                uint8_t SoundSize : 1;    //< 采样尺寸；
                uint8_t SoundType : 1;    //< 单声道或立体声。
                union {
                    struct {
                        uint8_t AACPacketType : 8;  //< AAC 包类型，头为 0，数据为 1。
                    } AACFormat;
                    uint8_t OtherFormat : 8;
                };
            } AudioType;
            struct {
                uint8_t FrameType : 4;  //< 帧类型；
                uint8_t CodecID : 4;    //< 视频格式。
                union {
                    struct {
                        uint8_t AVCPacketType : 8;     //< AVC 包类型，头为 0，NALU 为 1，尾为 2；
                        int32_t CompositionTime : 24;  //< 合成时间。
                    } AVCCodec;
                    uint32_t OtherType : 32;
                };
            } VudioType;
        };
    };
    /// FLV 文件体 上一 Tag 尺寸（FLV Body Previous Tag Size）。
    struct FLVBPTS {
        uint32_t PreviousTagSize : 32;  //< 上一 Tag 尺寸。
    };

    /// 检验输入数据是否符合 FLV Header。
    /** \param[in] data
     *  \param[in] len
     */
    static bool IsFLVHeader(
        const uint8_t * const data, const size_t len)
    {
        if (len < sizeof(FLVH)) return false;
        if (0x46u != data[0] || 0x4Cu != data[1] || 0x56u != data[2]) return false;
        return true;
    }

    /// 检验输入数据是否符合 FLV Body Tag Header。
    /** \param[in] data
     *  \param[in] len
     *  \param[in] maxDataSize 额外限制最大数据区尺寸，用以更精确检验。
     */
    static bool IsFLVBodyTagHeader(
        const uint8_t * const data, const size_t len,
        const size_t maxDataSize = 0)
    {
        if (len < sizeof(FLVBTH)) return false;
        if (0x08u != data[0] && 0x09u != data[0] && 0x12u != data[0]) return false;
        if (0 != maxDataSize) {
            auto DataSize = static_cast<uint32_t>(data[1]) << 16 |
                static_cast<uint32_t>(data[2]) << 8 |
                static_cast<uint32_t>(data[3]);
            if (maxDataSize < DataSize) return false;
        }
        if (0x00u != data[8] || 0x00u != data[9] || 0x00u != data[10]) return false;
        return true;
    }

    /// 解析 FLV Header。
    /** \param[out]    flvh
     *  \param[in]     data
     *  \param[in,out] cur
     *  \param[in]     len
     */
    static bool ParseFLVHeader(
        FLVH &flvh, const uint8_t * const data, size_t &cur, const size_t len)
    {
        if (len < cur + sizeof(FLVH)) return false;
        auto flvhpos = cur;
        flvh.Signature = static_cast<uint32_t>(data[cur]) << 16 |
            static_cast<uint32_t>(data[cur + 1]) << 8 |
            static_cast<uint32_t>(data[cur + 2]);
        cur += 3;
        flvh.Version = data[cur];
        cur += 1;
        flvh.TypeFlagsReserved5 = (data[cur] & 0xF8u) >> 3;
        flvh.TypeFlagsAudio = (data[cur] & 0x04u) >> 2;
        flvh.TypeFlagsReserved1 = (data[cur] & 0x02u) >> 1;
        flvh.TypeFlagsVideo = (data[cur] & 0x01u) >> 0;
        cur += 1;
        flvh.DataOffset = static_cast<uint32_t>(data[cur]) << 24 |
            static_cast<uint32_t>(data[cur + 1]) << 16 |
            static_cast<uint32_t>(data[cur + 2]) << 8 |
            static_cast<uint32_t>(data[cur + 3]);
        cur = flvhpos + flvh.DataOffset;
        return true;
    }

    /// 解析 FLV Body Previous Tag Size。
    /** \param[out]    flvbpts
     *  \param[in]     data
     *  \param[in,out] cur
     *  \param[in]     len
     */
    static bool ParseFLVBodyPreviousTagSize(
        FLVBPTS &flvbpts, const uint8_t * const data, size_t &cur, const size_t len)
    {
        if (len < cur + sizeof(FLVBPTS)) return false;
        flvbpts.PreviousTagSize = static_cast<uint32_t>(data[cur]) << 24 |
            static_cast<uint32_t>(data[cur + 1]) << 16 |
            static_cast<uint32_t>(data[cur + 2]) << 8 |
            static_cast<uint32_t>(data[cur + 3]);
        cur += 4;
        return true;
    }

    /// 解析 FLV Body Tag Header。
    /** \param[out]    flvbth
     *  \param[in]     data
     *  \param[in,out] cur
     *  \param[in]     len
     */
    static bool ParseFLVBodyTagHeader(
        FLVBTH &flvbth, const uint8_t * const data, size_t &cur, const size_t len)
    {
        if (len < cur + sizeof(FLVBTH)) return false;
        flvbth.TagType = data[cur];
        cur += 1;
        flvbth.DataSize = static_cast<uint32_t>(data[cur]) << 16 |
            static_cast<uint32_t>(data[cur + 1]) << 8 |
            static_cast<uint32_t>(data[cur + 2]);
        cur += 3;
        flvbth.Timestamp = static_cast<uint32_t>(data[cur]) << 16 |
            static_cast<uint32_t>(data[cur + 1]) << 8 |
            static_cast<uint32_t>(data[cur + 2]);
        cur += 3;
        flvbth.TimestampExtended = data[cur];
        cur += 1;
        flvbth.StreamID = static_cast<uint32_t>(data[cur]) << 16 |
            static_cast<uint32_t>(data[cur + 1]) << 8 |
            static_cast<uint32_t>(data[cur + 2]);
        cur += 3;
        return true;
    }

    /// 解析 FLV Body Tag Data。
    /** \param[in]     flvbth
     *  \param[out]    flvbtd
     *  \param[in]     data
     *  \param[in,out] cur
     *  \param[in]     len
     *  \todo Script tag parse.
     */
    static bool ParseFLVBodyTagData(
        const FLVBTH &flvbth, FLVBTD &flvbtd, const uint8_t * const data, size_t &cur, const size_t len)
    {
        if (len < cur + sizeof(FLVBTD)) return false;
        if (0x08u == flvbth.TagType) {
            flvbtd.AudioType.SoundFormat = (data[cur] & 0xF0u) >> 4;
            flvbtd.AudioType.SoundRate = (data[cur] & 0x0Cu) >> 2;
            flvbtd.AudioType.SoundSize = (data[cur] & 0x02u) >> 1;
            flvbtd.AudioType.SoundType = (data[cur] & 0x01u) >> 0;
            cur += 1;
            if (0x0Au == flvbtd.AudioType.SoundFormat) {
                flvbtd.AudioType.AACFormat.AACPacketType = data[cur];
                cur += 1;
            }
        } else if (0x09u == flvbth.TagType) {
            flvbtd.VudioType.FrameType = (data[cur] & 0xF0u) >> 4;
            flvbtd.VudioType.CodecID = (data[cur] & 0x0Fu) >> 0;
            cur += 1;
            if (0x07u == flvbtd.VudioType.CodecID) {
                flvbtd.VudioType.AVCCodec.AVCPacketType = data[cur];
                cur += 1;
                flvbtd.VudioType.AVCCodec.CompositionTime = static_cast<uint32_t>(data[cur]) << 16 |
                    static_cast<uint32_t>(data[cur + 1]) << 8 |
                    static_cast<uint32_t>(data[cur + 2]);
                cur += 3;
            }
        } else if (0x12u == flvbth.TagType) {
            // TODO: Script tag parse
        } else {
            return false;
        }
        return true;
    }
};

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_FLVDEMUX_HPP
