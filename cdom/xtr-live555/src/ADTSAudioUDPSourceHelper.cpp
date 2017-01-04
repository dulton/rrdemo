/** \copyright The MIT License */
#include "ADTSAudioUDPSourceHelper.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

std::map<u_int16_t, ADTSAudioUDPSourceHelper *> ADTSAudioUDPSourceHelper::map;
std::mutex ADTSAudioUDPSourceHelper::mtx;

bool ADTSAudioUDPSourceHelper::allo(UsageEnvironment * const env, const u_int16_t port)
{
    if (map.end() != map.find(port)) return false;
    mtx.lock(); {
        map.insert(std::pair<u_int16_t, ADTSAudioUDPSourceHelper *>(
            port, createNew(*env, port)));
    } mtx.unlock();
    return true;
}

ADTSAudioUDPSourceHelper *ADTSAudioUDPSourceHelper::find(const u_int16_t port)
{
    if (map.end() == map.find(port)) return nullptr;
    return map[port];
}

void ADTSAudioUDPSourceHelper::newpck(const PACKET &pck, const SOCKADDR_IN &, const SOCKADDR_IN &)
{
    if (pck.len < sizeof(ADTSFH))
        return;

    ADTSFH parsor;
    memcpy_s(&parsor, sizeof parsor, pck.data, sizeof(ADTSFH));

    if (0xFFF != parsor.syncword)
        return;

    if (3 == parsor.profile) {
        envir() << "ADTSAudioUDPSourceHelper: Bad profile.\n";
        return;
    }

    if (0 == SAMPLING_FREQUENCY_TABLE[parsor.sampling_frequency_index]) {
        envir() << "ADTSAudioUDPSourceHelper: Bad sampling_frequency_index.\n";
        return;
    }

    if (0 == CHANNEL_CONFIGURATION_TABLE[parsor.channel_configuration]) {
        envir() << "ADTSAudioUDPSourceHelper: Bad channel_configuration.\n";
        return;
    }

    memcpy_s(&adtsfh, sizeof adtsfh, &parsor, sizeof parsor);
    sprintf_s(configstr_, sizeof configstr_, "%02X%02x",
              adtsfh.profile + 1 << 3 | adtsfh.sampling_frequency_index >> 1,
              adtsfh.sampling_frequency_index << 7 | adtsfh.channel_configuration << 3);

#ifndef NDEBUG
    envir() << "ADTSAudioUDPSourceHelper: profile " << parsor.profile << ","
        << " sampling_frequency_index " << parsor.sampling_frequency_index << ","
        << " channel_configuration " << parsor.channel_configuration << ".\n";
#endif
}


}// namespace live555
}// namespace cdom
}// namespace rrdemo
