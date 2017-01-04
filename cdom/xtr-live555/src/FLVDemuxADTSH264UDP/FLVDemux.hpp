/** \file
 *  \author zhengrr
 *  \date 2017-1-4
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
        uint8_t TypeFlagsReserved : 5;   //< 固定为 0；
        uint8_t TypeFlagsAudio : 1;      //< 音频标志位；
        uint8_t TypeFlagsReserved2 : 1;  //< 固定为 0；
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
                    } AACType;
                    uint8_t Normal2ndByte : 8;
                };
                uint8_t Normal3rd4rd5rdBytes : 24;
            } AudioType;
            struct {
                uint8_t FrameType : 4;  //< 帧类型；
                uint8_t CodecID : 4;    //< 视频格式。
                union {
                    struct {
                        uint8_t AVCPacketType : 8;     //< AVC 包类型，头为 0，NALU 为 1，尾为 2；
                        int32_t CompositionTime : 24;  //< 合成时间。
                    } AVCType;
                    uint8_t Normal2nd3rd4rd5rdBytes : 32;
                };
            } VudioType;
        };
    };
    /// FLV 文件体 上一 Tag 尺寸（FLV Body Previous Tag Size）。
    struct FLVBPTS {
        uint32_t PreviousTagSize : 32;  //< 上一 Tag 尺寸。
    };
};

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_FLVDEMUX_HPP
