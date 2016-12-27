/** \file
 *  \author zhengrr
 *  \date 2016-12-22 – 27
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_H264VIDEOFIFOSERVERMEDIASUBSESSION_HPP
#define _RRDEMOCDOMLIVE555_H264VIDEOFIFOSERVERMEDIASUBSESSION_HPP

#include <live555/OnDemandServerMediaSubsession.hh>

#include "H264VideoFIFOSource.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

#ifdef CODING

class H264VideoFIFOServerMediaSubsession : public OnDemandServerMediaSubsession {
public:
    static H264VideoFIFOServerMediaSubsession *createNew(
        UsageEnvironment &env, FramedSource *src);

protected:
    H264VideoFIFOServerMediaSubsession(
        UsageEnvironment &env, H264VideoFifoSource *src);

    ~H264VideoFIFOServerMediaSubsession();

    FramedSource *createNewStreamSource(unsigned clientSessionId,
                                        unsigned &estBitrate) override;

    RTPSink *createNewRTPSink(Groupsock *rtpGroupsock,
                              unsigned char rtpPayloadTypeIfDynamic,
                              FramedSource *inputSource) override;

};// H264VideoFIFOServerMediaSubsession

#endif// CODING

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_H264VIDEOFIFOSERVERMEDIASUBSESSION_HPP
