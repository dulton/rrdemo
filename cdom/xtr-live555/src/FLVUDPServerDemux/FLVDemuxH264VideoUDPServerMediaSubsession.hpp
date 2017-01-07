/** \file
 *  \author zhengrr
 *  \date 2017-1-4
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_FLVDEMUXH264VIDEOUDPSERVERMEDIASUBSESSION_HPP
#define _RRDEMOCDOMLIVE555_FLVDEMUXH264VIDEOUDPSERVERMEDIASUBSESSION_HPP

#include <live555/OnDemandServerMediaSubsession.hh>

namespace rrdemo {
namespace cdom {
namespace live555 {

class FLVDemuxH264VideoUDPServerMediaSubsession : public OnDemandServerMediaSubsession {
public:
    static FLVDemuxH264VideoUDPServerMediaSubsession *createNew(UsageEnvironment &env, const u_int16_t port)
    {
        return new FLVDemuxH264VideoUDPServerMediaSubsession(env, port);  // leak
    }

protected:
    explicit FLVDemuxH264VideoUDPServerMediaSubsession(UsageEnvironment &env, const u_int16_t port) :
        OnDemandServerMediaSubsession(env, True), port {port}
    {}

    ~FLVDemuxH264VideoUDPServerMediaSubsession()
    {}

    FramedSource *createNewStreamSource(unsigned clientSessionId,
                                        unsigned &estBitrate) override;

    RTPSink *createNewRTPSink(Groupsock *rtpGroupsock,
                              unsigned char rtpPayloadTypeIfDynamic,
                              FramedSource *inputSource) override;

    u_int16_t port;

};// class FLVDemuxH264VideoUDPServerMediaSubsession 

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_FLVDEMUXH264VIDEOUDPSERVERMEDIASUBSESSION_HPP
