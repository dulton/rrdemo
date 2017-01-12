/** \file
 *  \author zhengrr
 *  \date 2017-1-11
 *  \copyright The MIT License
 */
#ifndef RRDEMO__CDOM__LIVE555__ADVANCED_VIDEO_CODING__HPP
#define RRDEMO__CDOM__LIVE555__ADVANCED_VIDEO_CODING__HPP

#include <cstdint>

namespace rrdemo {
namespace cdom {
namespace live555 {

/// Advanced Video Coding Sequence Header
/** 因端序和实现差异导致的不可移植性，位域结构体仅供按字段访问，勿按内存整体访问。
 */
struct AVCSequenceHeader {
    uint8_t configurationVersion : 8;  ///< 固为 1；
    uint8_t avcProfileIndication : 8;
    uint8_t profileCompatibility : 8;
    uint8_t avcLevelIndication : 8;
    uint8_t reserver6 : 6;             ///< 固为 111111(2)；
    uint8_t lengthSizeMinusOne : 2;
    uint8_t reserver3 : 3;             ///< 固为 111(2);
    uint8_t numOfSequenceParameterSets : 5;
    struct SequenceParameterSet {
        uint16_t length : 16;
        uint8_t *nalUnit;
    } *sequenceParameterSets;
    uint8_t numOfPictureParameterSets : 8;
    struct PictureParameterSet {
        uint16_t length : 16;
        uint8_t *nalUnit;
    } *pictureParameterSets;
    uint8_t getNumOfSPSs() const { return numOfSequenceParameterSets; }
    SequenceParameterSet *getSPSs() const { return sequenceParameterSets; }
    uint8_t getNumOfPPSs() const { return numOfPictureParameterSets; }
    static const size_t MINIMUM_SIZE {7/*bytes*/};
    static bool Parse(AVCSequenceHeader &avcSequenceHeader, const uint8_t * const data, const size_t length);
    bool parse(const uint8_t * const data, const size_t length) { return Parse(*this, data, length); }
    bool allocated {false};
    ~AVCSequenceHeader();
};

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// RRDEMO__CDOM__LIVE555__ADVANCED_VIDEO_CODING__HPP