/** \copyright The MIT License */
#include "FlashVideoDemultiplexer.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

bool FlashVideoDemultiplexer::gIsFlashVideoHeader(const uint8_t * const data, const size_t len)
{
    if (len < sizeof(FLVH_)) return false;
    if (0x46 != data[0] || 0x4Cu != data[1] || 0x56u != data[2]) return false;
    return true;
}

bool FlashVideoDemultiplexer::gIsFlashVideoBodyTagHeader(const uint8_t * const data, const size_t len,
                                                         const size_t maxDataSize = 0)
{
    if (len < sizeof(FLVBTH_)) return false;
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

bool FlashVideoDemultiplexer::gParseFlashVideoHeader(FLVH_ &flvh,
                                                     const uint8_t * const data, size_t &cur, const size_t len)
{
    if (len < cur + sizeof(FLVH_)) return false;
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

bool FlashVideoDemultiplexer::gParseFLVBodyPreviousTagSize(FLVBPTS_ &flvbpts,
                                                           const uint8_t * const data, size_t &cur, const size_t len)
{
    if (len < cur + sizeof(FLVBPTS_)) return false;
    flvbpts.PreviousTagSize = static_cast<uint32_t>(data[cur]) << 24 |
        static_cast<uint32_t>(data[cur + 1]) << 16 |
        static_cast<uint32_t>(data[cur + 2]) << 8 |
        static_cast<uint32_t>(data[cur + 3]);
    cur += 4;
    return true;
}

bool FlashVideoDemultiplexer::gParseFLVBodyTagHeader(FLVBTH_ &flvbth,
                                                     const uint8_t * const data, size_t &cur, const size_t len)
{
    if (len < cur + sizeof(FLVBTH_)) return false;
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

bool FlashVideoDemultiplexer::gParseFLVBodyTagData(const FLVBTH_ &flvbth,
                                                   FLVBTD_ &flvbtd,
                                                   const uint8_t * const data, size_t &cur, const size_t len)
{
    if (len < cur + sizeof(FLVBTD_)) return false;
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

}// namespace live555
}// namespace cdom
}// namespace rrdemo
