/** \copyright The MIT License */
#include "AudioDataTransportStreamFrame.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

const size_t AudioDataTransportStreamFrame::HEADER_SIZE = 7/*Bytes*/;

const unsigned AudioDataTransportStreamFrame::SAMPLING_FREQUENCY_TABLE[16] {
    96000, 88200, 64000, 48000, 44100, 32000, 24000, 22050, 16000, 12000, 11025, 8000, 7350, 0, 0, 0
};

const unsigned AudioDataTransportStreamFrame::CHANNEL_CONFIGURATION_TABLE[8] {
    2, 1, 2, 3, 4, 5, 6, 8
};

bool AudioDataTransportStreamFrame::
IsHeader(const uint8_t * const data, const size_t len)
{
    if (len < HEADER_SIZE)
        return false;
    if (0xFFu == data[0] && 0xF0u == (data[1] & 0xF0u))
        return true;
    return false;
}

bool AudioDataTransportStreamFrame::
ParseHeader(ADTSFHeader &header, const uint8_t * const data, const size_t len)
{
    if (!IsHeader(data, len))
        return false;
    header.syncword = static_cast<uint16_t>(data[0]) << 4 |
        static_cast<uint16_t>(data[1] & 0xF0u) >> 4;
    header.profile = (data[2] & 0xC0u) >> 6;
    header.sampling_frequency_index = (data[2] & 0x3Cu) >> 2;
    header.channel_configuration = (data[2] & 0x01u) << 2 |
        (data[3] & 0xC0u) >> 6;
    return true;
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
