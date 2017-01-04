/** \copyright The MIT License */
#include "ADTSAudioUDPServerMediaSubsession.hpp"

#include <live555/MPEG4GenericRTPSink.hh>

#include "ADTSAudioUDPSource.hpp"
#include "ADTSAudioUDPSourceHelper.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

FramedSource *ADTSAudioUDPServerMediaSubsession::createNewStreamSource(
    unsigned /*clientSessionId*/, unsigned &estBitrate)
{
    estBitrate = 96/*kbps*/;
    return ADTSAudioUDPSource::createNew(envir(), port);
}

RTPSink *ADTSAudioUDPServerMediaSubsession::createNewRTPSink(
    Groupsock *rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource *inputSource)
{
    ADTSAudioUDPSource *src;

    do {
        src = static_cast<ADTSAudioUDPSource *>(inputSource);
        if (src->initialized()) break;
        src = ADTSAudioUDPSourceHelper::find(port);
        if (nullptr != src && src->initialized()) break;
        src = static_cast<ADTSAudioUDPSource *>(inputSource);
        assert(false);
    } while (false);

    return MPEG4GenericRTPSink::createNew(
        envir(), rtpGroupsock, rtpPayloadTypeIfDynamic,
        src->sampfreq(), "audio", "AAC-hbr", src->configstr(), src->channels());
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
