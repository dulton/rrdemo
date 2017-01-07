/** \file
 *  \author zhengrr
 *  \date 2017-1-4
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_FLVDEMUXADTSAUDIOUDPSERVERMEDIASUBSESSION_HPP
#define _RRDEMOCDOMLIVE555_FLVDEMUXADTSAUDIOUDPSERVERMEDIASUBSESSION_HPP

#include <live555/OnDemandServerMediaSubsession.hh>

namespace rrdemo {
namespace cdom {
namespace live555 {

class FLVDemuxADTSAudioUDPServerMediaSubsession : public OnDemandServerMediaSubsession {
public:
    static FLVDemuxADTSAudioUDPServerMediaSubsession *createNew(UsageEnvironment &env, const u_int16_t port)
    {
        return new FLVDemuxADTSAudioUDPServerMediaSubsession(env, port);  // leak
    }

protected:
    explicit FLVDemuxADTSAudioUDPServerMediaSubsession(UsageEnvironment &env, const u_int16_t port) :
        OnDemandServerMediaSubsession(env, True), port {port}
    {}

    ~FLVDemuxADTSAudioUDPServerMediaSubsession()
    {};

    FramedSource *createNewStreamSource(unsigned clientSessionId,
                                        unsigned &estBitrate) override;

    RTPSink *createNewRTPSink(Groupsock *rtpGroupsock,
                              unsigned char rtpPayloadTypeIfDynamic,
                              FramedSource *inputSource) override;

    u_int16_t port;

};// class FLVDemuxADTSAudioUDPServerMediaSubsession

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_FLVDEMUXADTSAUDIOUDPSERVERMEDIASUBSESSION_HPP
