/** \copyright The MIT License */
#include "FLVDemuxH264VideoUDPServerMediaSubsession.hpp"

#include <live555/H264VideoRTPSink.hh>
#include <live555/H264VideoStreamFramer.hh>

#include "FLVDemuxH264VideoUDPSource.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

FramedSource *FLVDemuxH264VideoUDPServerMediaSubsession::createNewStreamSource(
    unsigned /*clientSessionId*/, unsigned &estBitrate)
{
    estBitrate = 500/*kbps*/;
    FramedSource *src = FLVDemuxH264VideoUDPSource::createNew(envir(), port);
    return H264VideoStreamFramer::createNew(envir(), src, True);
}

RTPSink *FLVDemuxH264VideoUDPServerMediaSubsession::createNewRTPSink(
    Groupsock* rtpGroupsock, unsigned char /*rtpPayloadTypeIfDynamic*/, FramedSource */*inputSource*/)
{
    return H264VideoRTPSink::createNew(envir(), rtpGroupsock, 96);
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
