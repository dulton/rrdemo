/** \copyright The MIT License */
#include "FLVDemuxADTSAudioUDPSource.hpp"

#include <thread>

#include "FLVDemuxADTSAudioUDPSourceHelper.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

void FLVDemuxADTSAudioUDPSource::initializeSourceBeforeEventLoop(UsageEnvironment* env, u_int16_t port)
{
    BasicUDPSource::initializeSourceBeforeEventLoop(env, port);
    FLVDemuxADTSAudioUDPSourceHelper::allo(env, port);
}

void FLVDemuxADTSAudioUDPSource::newpck(const PACKET &pck, const SOCKADDR_IN &, const SOCKADDR_IN &)
{
    bool isheader;
    do {
        if (pck.len < sizeof(ADTSFH)) {
            isheader = false; break;
        }

        if (!(0xFFu == pck.data[0] && 0xF0u == (pck.data[1] & 0xF0u))) {
            isheader = false; break;
        }
        adtsfh.syncword = 0xFFFu;

        uint8_t profile {(pck.data[2] & 0xC0u) >> 6};
        if (3 == profile) {
            envir() << "FLVDemuxADTSAudioUDPSource: Bad profile.\n";
            isheader = false; break;
        }
        adtsfh.profile = profile;

        uint8_t sampling_frequency_index {(pck.data[2] & 0x3Cu) >> 2};
        if (0 == SAMPLING_FREQUENCY_TABLE[sampling_frequency_index]) {
            envir() << "FLVDemuxADTSAudioUDPSource: Bad sampling_frequency_index.\n";
            isheader = false; break;
        }
        adtsfh.sampling_frequency_index = sampling_frequency_index;

        uint8_t channel_configuration {(pck.data[2] & 0x01u) << 2 | (pck.data[3] & 0xC0u) >> 6};
        if (0 == CHANNEL_CONFIGURATION_TABLE[channel_configuration]) {
            envir() << "FLVDemuxADTSAudioUDPSource: Bad channel_configuration.\n";
            isheader = false; break;
        }
        adtsfh.channel_configuration = channel_configuration;

        isheader = true;
        initialized_ = true;

    } while (false);

    /* 若上一帧已组装完毕，则将其压入缓存池，并重置 ADTS 帧缓存 */
    if (isheader && 0 < adtsfb.len) {
        Buf *buf;
        while (nullptr == (buf = bufs.allocateforce()))
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        const auto discarded = buf->cpyf(adtsfb.data, adtsfb.len);
        if (0 < discarded)
            envir() << "FLVDemuxADTSAudioUDPSource: A ADTSFB size is too large for SrcBuf, "
            << discarded << " bytes data has been discarded.\n";
        bufs.push(buf);
        adtsfb.len = 0;
        adtsfb.pcknum = 0;
    } else
        if (ceil(adtsfb.SIZE / pck.SIZE) / 0.01 - 1 < ++adtsfb.pcknum &&
            0 == adtsfb.pcknum % static_cast<int>(ceil(adtsfb.SIZE / pck.SIZE)))
            envir() << "FLVDemuxADTSAudioUDPSource: " << adtsfb.pcknum << " consecutive packets without NALU start_codes,"
            << " the port is receiving audio data transport stream?";

    /* 将包数据追加至 ADTS 帧缓存 */
    const auto free = adtsfb.SIZE - adtsfb.len;
    const auto actual = pck.len < free ? pck.len : free;  // min
    memcpy_s(adtsfb.data + adtsfb.len, free, pck.data, actual);
    adtsfb.len += actual;
    const auto discarded = pck.len - actual;
    if (0 < discarded)
        envir() << "FLVDemuxADTSAudioUDPSource: A ADTSF size is too large for ADTSFB, "
        << discarded << " bytes data has been discarded.\n";
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
