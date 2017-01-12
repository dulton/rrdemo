/** \copyright The MIT License */
#include "AdvancedVideoCoding.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

bool AVCSequenceHeader::
Parse(AVCSequenceHeader &seqHdr, const uint8_t* const data, const size_t len)
{
    if (len < MINIMUM_SIZE) return false;
    seqHdr.configurationVersion = data[0];
    seqHdr.avcProfileIndication = data[1];
    seqHdr.profileCompatibility = data[2];
    seqHdr.avcLevelIndication = data[3];
    seqHdr.reserver6 = (data[4] & 0xFCu) >> 2;
    if (0x3Fu != seqHdr.reserver6) return false;
    seqHdr.lengthSizeMinusOne = data[4] & 0x03u;
    seqHdr.reserver3 = (data[5] & 0xE0u) >> 5;
    if (0x7u != seqHdr.reserver3) return false;
    seqHdr.numOfSequenceParameterSets = data[5] & 0x1Fu;
    /* Validate */
    size_t cur {6};  // cursor, offset 6, ordinal 7
    uint16_t spsLen;
    for (auto i = 0; i < seqHdr.getNumOfSPSs(); ++i) {
        if (len < cur + 2) return false;
        spsLen = static_cast<uint16_t>(data[cur]) << 8 |
            static_cast<uint16_t>(data[cur + 1]);
        cur += 2;
        if (len < cur + spsLen) return false;
        cur += spsLen;
    }
    if (len < cur + 2) return false;
    seqHdr.numOfPictureParameterSets = static_cast<uint16_t>(data[cur]) << 8 |
        static_cast<uint16_t>(data[cur + 1]);
    cur += 2;
    uint16_t ppsLen;
    for (auto i = 0; i < seqHdr.getNumOfPPSs(); ++i) {
        if (len < cur + 2) return false;
        ppsLen = static_cast<uint16_t>(data[cur]) << 8 |
            static_cast<uint16_t>(data[cur + 1]);
        cur += 2;
        if (len < cur + ppsLen) return false;
        cur += ppsLen;
    }
    /* TODO:Allocate */
    seqHdr.allocated = true;
    return true;
}

AVCSequenceHeader::
~AVCSequenceHeader()
{
    if (!allocated) return;
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
