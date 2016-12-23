/** \file
 *  \author zhengrr
 *  \date 2016-12-22
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_H264VIDEOFIFOSERVERMEDIASUBSESSION_HPP
#define _RRDEMOCDOMLIVE555_H264VIDEOFIFOSERVERMEDIASUBSESSION_HPP

#include <live555/OnDemandServerMediaSubsession.hh>

#include "h264_video_fifo_source.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

#ifdef CODING

class H264VideoFifoServerMediaSubsession : public OnDemandServerMediaSubsession {
public:
    static H264VideoFifoServerMediaSubsession *createNew(
        UsageEnvironment &env, FramedSource *src);

protected:
    H264VideoFifoServerMediaSubsession(
        UsageEnvironment &env, H264VideoFifoSource *src);

    ~H264VideoFifoServerMediaSubsession();

    FramedSource *createNewStreamSource(unsigned clientSessionId,
                                        unsigned &estBitrate) override;

    RTPSink *createNewRTPSink(Groupsock *rtpGroupsock,
                              unsigned char rtpPayloadTypeIfDynamic,
                              FramedSource *inputSource) override;

};// H264VideoFifoServerMediaSubsession

#endif// CODING

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_H264VIDEOFIFOSERVERMEDIASUBSESSION_HPP
