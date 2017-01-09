/** \file
 *  \author zhengrr
 *  \date 2016-12-15 – 2017-1-3
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_H264VIDEOUDPSERVERMEDIASUBSESSION_HPP
#define _RRDEMOCDOMLIVE555_H264VIDEOUDPSERVERMEDIASUBSESSION_HPP

#include <live555/OnDemandServerMediaSubsession.hh>

namespace rrdemo {
namespace cdom {
namespace live555 {

class H264VideoUDPServerMediaSubsession : public OnDemandServerMediaSubsession {
public:
    static H264VideoUDPServerMediaSubsession *createNew(UsageEnvironment &env, const u_int16_t port)
    {
        return new H264VideoUDPServerMediaSubsession(env, port);  // leak
    }

protected:
    explicit H264VideoUDPServerMediaSubsession(UsageEnvironment &env, const u_int16_t port) :
        OnDemandServerMediaSubsession(env, True), port {port}
    {}

    ~H264VideoUDPServerMediaSubsession()
    {}

    FramedSource *createNewStreamSource(unsigned clientSessionId,
                                        unsigned &estBitrate) override;

    RTPSink *createNewRTPSink(Groupsock *rtpGroupsock,
                              unsigned char rtpPayloadTypeIfDynamic,
                              FramedSource *inputSource) override;

    u_int16_t port;

};// class H264VideoUDPServerMediaSubsession 

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_H264VIDEOUDPSERVERMEDIASUBSESSION_HPP
