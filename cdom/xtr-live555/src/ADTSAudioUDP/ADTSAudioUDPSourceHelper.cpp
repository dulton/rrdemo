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

    if (!(0xFFu == pck.data[0] && 0xF0u == (pck.data[1] & 0xF0u)))
        return;
    adtsfh.syncword = 0xFFFu;

    uint8_t profile {(pck.data[2] & 0xC0u) >> 6};
    if (3 == profile) {
        envir() << "ADTSAudioUDPSourceHelper: Bad profile.\n";
        return;
    }
    adtsfh.profile = profile;

    uint8_t sampling_frequency_index {(pck.data[2] & 0x3Cu) >> 2};
    if (0 == SAMPLING_FREQUENCY_TABLE[sampling_frequency_index]) {
        envir() << "ADTSAudioUDPSourceHelper: Bad sampling_frequency_index.\n";
        return;
    }
    adtsfh.sampling_frequency_index = sampling_frequency_index;

    uint8_t channel_configuration {(pck.data[2] & 0x01u) << 2 | (pck.data[3] & 0xC0) >> 6};
    if (0 == CHANNEL_CONFIGURATION_TABLE[channel_configuration]) {
        envir() << "ADTSAudioUDPSourceHelper: Bad channel_configuration.\n";
        return;
    }
    adtsfh.channel_configuration = channel_configuration;

    initialized_ = true;
}


}// namespace live555
}// namespace cdom
}// namespace rrdemo
