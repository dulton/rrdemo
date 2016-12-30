/** \file
 *  \author zhengrr
 *  \date 2016-12-15 – 30
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
    static H264VideoUDPServerMediaSubsession *createNew(
        UsageEnvironment &env, const char const *addr, const Port &port, Boolean udp = False);

protected:
    explicit H264VideoUDPServerMediaSubsession(
        UsageEnvironment &env, const char const *addr, const Port &port, Boolean udp);

    ~H264VideoUDPServerMediaSubsession();

    FramedSource *createNewStreamSource(unsigned clientSessionId,
                                        unsigned &estBitrate) override;

    RTPSink *createNewRTPSink(Groupsock *rtpGroupsock,
                              unsigned char rtpPayloadTypeIfDynamic,
                              FramedSource *inputSource) override;

    const char const *addr {nullptr};
    Port port;
    Groupsock *skt {nullptr};
    Boolean udp;
};

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_H264VIDEOUDPSERVERMEDIASUBSESSION_HPP
