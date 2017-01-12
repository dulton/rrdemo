/** \copyright The MIT License */
#include "FlashVideo.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

bool FLVHeader::
Parse(FLVHeader &hdr, const uint8_t * const data, const size_t len)
{
    if (len < MINIMUM_SIZE) return false;
    hdr.signature = static_cast<uint32_t>(data[0]) << 16 |
        static_cast<uint32_t>(data[1]) << 8 |
        static_cast<uint32_t>(data[2]);
    if (0x464C56u != hdr.signature) return false;
    hdr.version = data[3];
    hdr.typeFlagsReserved5 = (data[4] & 0xF8u) >> 3;
    if (0x0u != hdr.typeFlagsReserved5) return false;
    hdr.typeFlagsAudio = (data[4] & 0x04u) >> 2;
    hdr.typeFlagsReserved1 = (data[4] & 0x02u) >> 1;
    if (0x0u != hdr.typeFlagsReserved1) return false;
    hdr.typeFlagsVideo = (data[4] & 0x01u) >> 0;
    hdr.dataOffset = static_cast<uint32_t>(data[5]) << 24 |
        static_cast<uint32_t>(data[6]) << 16 |
        static_cast<uint32_t>(data[7]) << 8 |
        static_cast<uint32_t>(data[8]);
    return true;
}

bool FLVPreviousTagSize::
Parse(FLVPreviousTagSize &preTagSize, const uint8_t * const data, const size_t len)
{
    if (len < SIZE) return false;
    preTagSize.previousTagSize = static_cast<uint32_t>(data[0]) << 24 |
        static_cast<uint32_t>(data[1]) << 16 |
        static_cast<uint32_t>(data[2]) << 8 |
        static_cast<uint32_t>(data[3]);
    return true;
}

bool FLVTagHeader::
Parse(FLVTagHeader &tagHdr, const uint8_t * const data, const size_t len)
{
    if (len < SIZE) return false;
    tagHdr.tagType = data[0];
    if (!tagHdr.isAudio() && !tagHdr.isVideo() && !tagHdr.isScript()) return false;
    tagHdr.dataSize = static_cast<uint32_t>(data[1]) << 16 |
        static_cast<uint32_t>(data[2]) << 8 |
        static_cast<uint32_t>(data[3]);
    if (tagHdr.isAudio() && tagHdr.getDataSize() < FLVTagDataAudio::MINIMUM_SIZE) return false;
    if (tagHdr.isVideo() && tagHdr.getDataSize() < FLVTagDataVideo::MINIMUM_SIZE) return false;
    if (tagHdr.isScript() && tagHdr.getDataSize() < FLVTagDataScript::MINIMUM_SIZE) return false;
    tagHdr.timestamp = static_cast<uint32_t>(data[4]) << 16 |
        static_cast<uint32_t>(data[5]) << 8 |
        static_cast<uint32_t>(data[6]);
    tagHdr.timestampExtended = data[7];
    tagHdr.streamID = static_cast<uint32_t>(data[8]) << 16 |
        static_cast<uint32_t>(data[9]) << 8 |
        static_cast<uint32_t>(data[10]);
    if (0x000u != tagHdr.streamID) return false;
    return true;
}

bool FLVTagDataAudio::
Parse(FLVTagDataAudio &tagData, const uint8_t * const data, const size_t len)
{
    if (len < MINIMUM_SIZE) return false;
    tagData.soundFormat = (data[0] & 0xF0u) >> 4;
    if (0x9u == tagData.soundFormat || 0xCu == tagData.soundFormat || 0xDu == tagData.soundFormat) return false;
    tagData.soundRate = (data[0] & 0x0Cu) >> 2;
    tagData.soundSize = (data[0] & 0x02u) >> 1;
    tagData.soundType = (data[0] & 0x01u) >> 0;
    if (tagData.isAAC()) {
        tagData.aacFormat.aacPacketType = data[1];
        if (0x1u < tagData.aacFormat.aacPacketType) return false;
    }
    return true;
}

bool FLVTagDataVideo::
Parse(FLVTagDataVideo &tagData, const uint8_t* const data, const size_t len)
{
    if (len < MINIMUM_SIZE) return false;
    tagData.frameType = (data[0] & 0xF0u) >> 4;
    if (tagData.frameType < 0x1u || 0x5u < tagData.frameType) return false;
    tagData.codecID = (data[0] & 0x0Fu) >> 0;
    if (tagData.codecID < 0x1u || 0x7u < tagData.codecID) return false;
    if (tagData.isAVC()) {
        tagData.avcCodec.avcPacketType = data[1];
        if (0x2u < tagData.avcCodec.avcPacketType) return false;
        tagData.avcCodec.compositionTime = static_cast<uint32_t>(data[2]) << 16 |
            static_cast<uint32_t>(data[3]) << 8 |
            static_cast<uint32_t>(data[4]);
        if (!tagData.isAVCNALU() && 0 != tagData.getCompositionTime()) return false;
    }
    return true;
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
