/** \copyright The MIT License */
#include "ADTSAudioUDPSource.hpp"

#include <thread>

#include "ADTSAudioUDPSourceHelper.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

const unsigned ADTSAudioUDPSource::SAMPLING_FREQUENCY_TABLE[16] {
    96000, 88200, 64000, 48000, 44100, 32000, 24000, 22050, 16000, 12000, 11025, 8000, 7350, 0, 0, 0
};

const unsigned ADTSAudioUDPSource::CHANNEL_CONFIGURATION_TABLE[16] {
    2, 1, 2, 3, 4, 5, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0
};

bool ADTSAudioUDPSource::initialized() const
{
    if (0xFFF == adtsfh.syncword) return true;
    else                          return false;
}

unsigned ADTSAudioUDPSource::sampfreq() const
{
    return SAMPLING_FREQUENCY_TABLE[adtsfh.sampling_frequency_index];
}

unsigned ADTSAudioUDPSource::usecspf() const
{
    return 1024. / sampfreq() * 1000 * 1000;
}

unsigned ADTSAudioUDPSource::channels() const
{
    return CHANNEL_CONFIGURATION_TABLE[adtsfh.channel_configuration];
}

const char *ADTSAudioUDPSource::configstr() const
{
    return configstr_;
}

void ADTSAudioUDPSource::initializeSourceBeforeEventLoop(UsageEnvironment* env, u_int16_t port)
{
    BasicUDPSource::initializeSourceBeforeEventLoop(env, port);
    ADTSAudioUDPSourceHelper::allo(env, port);
}

void ADTSAudioUDPSource::newpck(const PACKET &pck, const SOCKADDR_IN &, const SOCKADDR_IN &)
{
    /* 判断包是否含有 ADTS 帧头，并更新 */
    bool isheader;
    do {
        if (pck.len < sizeof(ADTSFH)) {
            isheader = false; break;
        }

        ADTSFH parsor;
        memcpy_s(&parsor, sizeof parsor, pck.data, sizeof(ADTSFH));

        if (0xFFF != parsor.syncword) {
            isheader = false; break;
        }

        if (3 == parsor.profile) {
            envir() << "ADTSAudioUDPSource: Bad profile.\n";
            isheader = false; break;
        }

        if (0 == SAMPLING_FREQUENCY_TABLE[parsor.sampling_frequency_index]) {
            envir() << "ADTSAudioUDPSource: Bad sampling_frequency_index.\n";
            isheader = false; break;
        }

        if (0 == CHANNEL_CONFIGURATION_TABLE[parsor.channel_configuration]) {
            envir() << "ADTSAudioUDPSource: Bad channel_configuration.\n";
            isheader = false; break;
        }

        isheader = true;
        memcpy_s(&adtsfh, sizeof adtsfh, &parsor, sizeof parsor);
        sprintf_s(configstr_, sizeof configstr_, "%02X%02x",
                  adtsfh.profile + 1 << 3 | adtsfh.sampling_frequency_index >> 1,
                  adtsfh.sampling_frequency_index << 7 | adtsfh.channel_configuration << 3);

    } while (false);

    if (isheader)
        envir() << "Header.\n";
    else
        envir() << "NOT Header.\n";

    /* 若上一帧已组装完毕，则将其压入缓存池，并重置 ADTS 帧缓存 */
    if (isheader && 0 < adtsfb.len) {
        Buf *buf;
        while (nullptr == (buf = bufs.allocateforce()))
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        const auto discarded = buf->cpyf(adtsfb.data, adtsfb.len);
        if (0 < discarded)
            envir() << "ADTSAudioUDPSource: A ADTSFB size is too large for SrcBuf, "
            << discarded << " bytes data has been discarded.\n";
        bufs.push(buf);
        adtsfb.len = 0;
        adtsfb.pcknum = 0;
    } else
        if (ceil(adtsfb.SIZE / pck.SIZE) / 0.01 - 1 < ++adtsfb.pcknum &&
            0 == adtsfb.pcknum % static_cast<int>(ceil(adtsfb.SIZE / pck.SIZE)))
            envir() << "ADTSAudioUDPSource: " << adtsfb.pcknum << " consecutive packets without NALU start_codes,"
            << " the port is receiving audio data transport stream?";

    /* 将包数据追加至 ADTS 帧缓存 */
    const auto free = adtsfb.SIZE - adtsfb.len;
    const auto actual = pck.len < free ? pck.len : free;  // min
    memcpy_s(adtsfb.data + adtsfb.len, free, pck.data, actual);
    adtsfb.len += actual;
    const auto discarded = pck.len - actual;
    if (0 < discarded)
        envir() << "ADTSAudioUDPSource: A ADTSF size is too large for ADTSFB, "
        << discarded << " bytes data has been discarded.\n";
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
