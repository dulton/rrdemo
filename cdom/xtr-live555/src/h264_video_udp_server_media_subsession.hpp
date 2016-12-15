/** \file
 *  \author zhengrr
 *  \date 2016-12-15
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_H264VIDEOUDPSERVERMEDIASUBSESSION_HPP
#define _RRDEMOCDOMLIVE555_H264VIDEOUDPSERVERMEDIASUBSESSION_HPP

#include <live555/OnDemandServerMediaSubsession.hh>

class H264VideoUDPServerMediaSubsession : public OnDemandServerMediaSubsession {
public:
    static H264VideoUDPServerMediaSubsession *createNew(
        UsageEnvironment &env, char const *addr, Port const &port, Boolean udp = False);
protected:
    explicit H264VideoUDPServerMediaSubsession(
        UsageEnvironment &env, char const *addr, Port const &port, Boolean udp);

    ~H264VideoUDPServerMediaSubsession();

    FramedSource *createNewStreamSource(unsigned clientSessionId,
                                        unsigned &estBitrate) override;

    RTPSink *createNewRTPSink(Groupsock* rtpGroupsock,
                              unsigned char rtpPayloadTypeIfDynamic,
                              FramedSource* inputSource) override;

    char const *addr;
    Port port;
    Groupsock *skt;
    Boolean udp;
};

#endif// _RRDEMOCDOMLIVE555_H264VIDEOUDPSERVERMEDIASUBSESSION_HPP
