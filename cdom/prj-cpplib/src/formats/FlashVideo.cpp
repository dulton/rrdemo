/** \copyright The MIT License */
#include "FlashVideo.hpp"

#include "../../prj-clib/src/parse_bit_stream.h"

namespace {
size_t Bb(const size_t Byte, const size_t bit = 0) { return 8 * Byte + bit; };
}

namespace rrdemo {
namespace cdom {
namespace cpp_library {

bool FLVTag::
Validate(const uint8_t * const data, const size_t size)
{

}

bool FLVTag::
parse(const uint8_t * const data, const size_t size)
{
    uint8_t tmp8;
    uint32_t tmp32;
    if (!zrr_parse8bits(&tmp8, data, size, 0, 2)) return false;
    if (0 != (reserved2 = tmp8)) return false;
    if (!zrr_parse8bits(&tmp8, data, size, 2, 1)) return false;
    filter = tmp8;
    if (!zrr_parse8bits(&tmp8, data, size, 3, 5)) return false;
    if (0 != (tagType = tmp8)) return false;
    if (!isAudio() && !isVideo() && !isScript()) return false;
    if (!zrr_parse32bits(&tmp32, data, size, Bb(1), Bb(3))) return false;
    dataSize = tmp32;
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

bool FLV::
Validate(const uint8_t * const data, const size_t length)
{
    FLV tmp;
    return tmp.parse(data, length);
}

bool FLV::
parse(const uint8_t * const data, const size_t length)
{
    uint8_t tmp8;
    uint32_t tmp32;
    if (!zrr_parse32bits(&tmp32, data, length, Bb(0, 0), Bb(2, 7))) return false;
    if ('FLV' != (signature = tmp32)) return false;
    if (!zrr_parse8bits(&tmp8, data, length, Bb(3, 0), Bb(3, 7))) return false;
    version = tmp8;
    if (!zrr_parse8bits(&tmp8, data, length, Bb(4, 0), Bb(4, 4))) return false;
    if (0 != (typeFlagsReserved5 = tmp8)) return false;
    if (!zrr_parse8bits(&tmp8, data, length, Bb(4, 5), Bb(4, 5))) return false;
    typeFlagsAudio = tmp8;
    if (!zrr_parse8bits(&tmp8, data, length, Bb(4, 6), Bb(4, 6))) return false;
    if (0 != (typeFlagsReserved1 = tmp8)) return false;
    if (!zrr_parse8bits(&tmp8, data, length, Bb(4, 7), Bb(4, 7))) return false;
    typeFlagsVideo = tmp8;
    if (!zrr_parse32bits(&tmp32, data, length, Bb(5, 0), Bb(8, 7))) return false;
    dataOffset = tmp32;
    if (!zrr_parse32bits(&tmp32, data, length, Bb(dataOffset, 0), Bb(dataOffset + 3, 7))) return false;
    if (0 != (previousTagSize0 = tmp32)) return false;
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

}// namespace cpp_library
}// namespace cdom
}// namespace rrdemo
