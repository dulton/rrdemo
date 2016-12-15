/** \copyright The MIT License */
#include "h264_video_udp_server_media_subsession.hpp"

#include <live555/BasicUDPSource.hh>
#include <live555/GroupsockHelper.hh>
#include <live555/SimpleRTPSink.hh>
#include <live555/SimpleRTPSource.hh>


H264VideoUDPServerMediaSubsession *H264VideoUDPServerMediaSubsession::createNew(
    UsageEnvironment &env, char const *addr, Port const &port, Boolean udp)
{
    return new H264VideoUDPServerMediaSubsession(env, addr, port, udp);
}

H264VideoUDPServerMediaSubsession::H264VideoUDPServerMediaSubsession(
    UsageEnvironment &env, char const *addr, Port const &port, Boolean udp) :
    OnDemandServerMediaSubsession(env, True), port {port}, skt {nullptr}, udp {udp}
{
    this->addr = strDup(addr);
}

H264VideoUDPServerMediaSubsession::~H264VideoUDPServerMediaSubsession()
{
    delete[] addr;
    delete skt;
}

FramedSource *H264VideoUDPServerMediaSubsession::createNewStreamSource(
    unsigned /*clientSessionId*/, unsigned &estBitrate)
{
    estBitrate = 5000/*kbps*/;

    if (!skt) {
        struct in_addr inaddr;
        inaddr.s_addr = addr ? our_inet_addr(addr) : 0;
        skt = new Groupsock(envir(), inaddr, port, 255);
    }

    FramedSource *src;
    if (udp) {
        src = BasicUDPSource::createNew(envir(), skt);
    } else {
        src = SimpleRTPSource::createNew(envir(), skt, 96, 90000, "video/H264", 0, False);
    }
    return src;
}

RTPSink *H264VideoUDPServerMediaSubsession::createNewRTPSink(
    Groupsock* rtpGroupsock, unsigned char /*rtpPayloadTypeIfDynamic*/, FramedSource */*inputSource*/)
{
    return SimpleRTPSink::createNew(
        envir(), rtpGroupsock, 96, 90000, "video", "H264", 1, True, False);
}
