/** \copyright The MIT License */
#include "FLVDemuxADTSAudioUDPServerMediaSubsession.hpp"

#include <live555/MPEG4GenericRTPSink.hh>

#include "FLVDemuxADTSAudioUDPSource.hpp"
#include "FLVDemuxADTSAudioUDPSourceHelper.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

FramedSource *FLVDemuxADTSAudioUDPServerMediaSubsession::createNewStreamSource(
    unsigned /*clientSessionId*/, unsigned &estBitrate)
{
    estBitrate = 96/*kbps*/;
    return FLVDemuxADTSAudioUDPSource::createNew(envir(), port);
}

RTPSink *FLVDemuxADTSAudioUDPServerMediaSubsession::createNewRTPSink(
    Groupsock *rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource *inputSource)
{
    FLVDemuxADTSAudioUDPSource *src;

    do {
        src = static_cast<FLVDemuxADTSAudioUDPSource *>(inputSource);
        if (src->initialized()) break;
        src = FLVDemuxADTSAudioUDPSourceHelper::find(port);
        if (nullptr != src && src->initialized()) break;
        src = static_cast<FLVDemuxADTSAudioUDPSource *>(inputSource);
        envir() << "FLVDemuxADTSAudioUDPServerMediaSubsession: No MPEG4GenericRTPSink information is available.\n";
    } while (false);

    return MPEG4GenericRTPSink::createNew(
        envir(), rtpGroupsock, rtpPayloadTypeIfDynamic,
        src->sampfreq(), "audio", "AAC-hbr", src->configstr(), src->channels());
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
