/** \copyright The MIT License */
#include "FlashVideo.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

const size_t FLVHeader::HEADER_MINIMUM_SIZE = 9/*bytes*/;

bool FLVHeader::
IsHeader(const uint8_t * const data, const size_t len)
{
    if (len < HEADER_MINIMUM_SIZE)
        return false;
    if (0x46 == data[0] && 0x4Cu == data[1] && 0x56u == data[2])
        return true;
    return false;
}

bool FLVHeader::
ParseHeader(FLVHeader &header, const uint8_t * const data, const size_t len)
{
    if (!IsHeader(data, len))
        return false;
    header.Signature = static_cast<uint32_t>(data[0]) << 16 |
        static_cast<uint32_t>(data[1]) << 8 |
        static_cast<uint32_t>(data[2]);
    header.Version = data[3];
    header.TypeFlagsReserved5 = (data[4] & 0xF8u) >> 3;
    header.TypeFlagsAudio = (data[4] & 0x04u) >> 2;
    header.TypeFlagsReserved1 = (data[4] & 0x02u) >> 1;
    header.TypeFlagsVideo = (data[4] & 0x01u) >> 0;
    header.DataOffset = static_cast<uint32_t>(data[5]) << 24 |
        static_cast<uint32_t>(data[6]) << 16 |
        static_cast<uint32_t>(data[7]) << 8 |
        static_cast<uint32_t>(data[8]);
    return true;
}

const size_t FLVPreviousTagSize::PREVIOUS_TAG_SIZE_SIZE = 4/*bytes*/;

bool FLVPreviousTagSize::
ParsePreviousTagSize(FLVPreviousTagSize &pts, const uint8_t * const data, const size_t len)
{
    if (len < PREVIOUS_TAG_SIZE_SIZE)
        return false;
    pts.PreviousTagSize = static_cast<uint32_t>(data[0]) << 24 |
        static_cast<uint32_t>(data[1]) << 16 |
        static_cast<uint32_t>(data[2]) << 8 |
        static_cast<uint32_t>(data[3]);
    return true;
}

const size_t FLVTagHeader::TAG_HEADER_SIZE = 11/*bytes*/;

bool FLVTagHeader::
IsTagHeader(const uint8_t * const data, const size_t len, const size_t maxDataSize)
{
    if (len < TAG_HEADER_SIZE)
        return false;
    if (!(0x08u == data[0] || 0x09u == data[0] || 0x12u == data[0]))
        return false;
    auto DataSize = static_cast<uint32_t>(data[1]) << 16 |
        static_cast<uint32_t>(data[2]) << 8 |
        static_cast<uint32_t>(data[3]);
    if (0 < maxDataSize && !(DataSize <= maxDataSize))
        return false;
    if (!(0x00u == data[8] && 0x00u == data[9] && 0x00u == data[10]))
        return false;
    return true;
}

bool FLVTagHeader::
ParseTagHeader(FLVTagHeader &tagHeader, const uint8_t * const data, const size_t len)
{
    if (!IsTagHeader(data, len))
        return false;
    tagHeader.TagType = data[0];
    tagHeader.DataSize = static_cast<uint32_t>(data[1]) << 16 |
        static_cast<uint32_t>(data[2]) << 8 |
        static_cast<uint32_t>(data[3]);
    tagHeader.Timestamp = static_cast<uint32_t>(data[4]) << 16 |
        static_cast<uint32_t>(data[5]) << 8 |
        static_cast<uint32_t>(data[6]);
    tagHeader.TimestampExtended = data[7];
    tagHeader.StreamID = static_cast<uint32_t>(data[8]) << 16 |
        static_cast<uint32_t>(data[9]) << 8 |
        static_cast<uint32_t>(data[10]);
    return true;
}

const size_t FLVTagDataAudio::TAG_DATA_AUDIO_MINIMUM_SIZE = 1/*bytes*/;

bool FLVTagDataAudio::
ParseTagData(FLVTagDataAudio &tagData, const uint8_t * const data, const size_t len)
{
    if (len < TAG_DATA_AUDIO_MINIMUM_SIZE)
        return false;
    tagData.soundFormat = (data[0] & 0xF0u) >> 4;
    tagData.soundRate = (data[0] & 0x0Cu) >> 2;
    tagData.soundSize = (data[0] & 0x02u) >> 1;
    tagData.soundType = (data[0] & 0x01u) >> 0;
    if (tagData.isAAC())
        tagData.aacFormat.aacPacketType = data[1];
    return true;
}

const size_t FLVTagDataVideo::TAG_DATA_VIDEO_MINIMUM_SIZE = 1/*bytes*/;

bool FLVTagDataVideo::
ParseTagData(FLVTagDataVideo &tagData, const uint8_t* const data, const size_t len)
{
    if (len < TAG_DATA_VIDEO_MINIMUM_SIZE)
        return false;
    tagData.frameType = (data[0] & 0xF0u) >> 4;
    tagData.codecID = (data[0] & 0x0Fu) >> 0;
    if (tagData.isAVC()) {
        tagData.avcCodec.avcPacketType = data[1];
        tagData.avcCodec.compositionTime = static_cast<uint32_t>(data[2]) << 16 |
            static_cast<uint32_t>(data[3]) << 8 |
            static_cast<uint32_t>(data[4]);
    }
    return true;
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
