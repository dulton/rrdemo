/** \copyright The MIT License */
#include "H264VideoUDPServerMediaSubsession.hpp"

#include <live555/GroupsockHelper.hh>
#include <live555/H264VideoRTPSink.hh>
#include <live555/H264VideoRTPSource.hh>
#include <live555/H264VideoStreamFramer.hh>

#include "H264VideoUDPSource.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

H264VideoUDPServerMediaSubsession *H264VideoUDPServerMediaSubsession::createNew(
    UsageEnvironment &env, const char const *addr, const Port &port, Boolean udp)
{
    return new H264VideoUDPServerMediaSubsession(env, addr, port, udp);
}

H264VideoUDPServerMediaSubsession::H264VideoUDPServerMediaSubsession(
    UsageEnvironment &env, const char const *addr, const Port &port, Boolean udp) :
    OnDemandServerMediaSubsession(env, True), port {port}, udp {udp}
{
    this->addr = strDup(addr);
}

H264VideoUDPServerMediaSubsession::~H264VideoUDPServerMediaSubsession()
{
    delete[] addr;
    if (skt) delete skt;
}

FramedSource *H264VideoUDPServerMediaSubsession::createNewStreamSource(
    unsigned /*clientSessionId*/, unsigned &estBitrate)
{
    estBitrate = 5000/*kbps*/;

    if (!skt) {
        struct in_addr inaddr;
        inaddr.s_addr = addr ? our_inet_addr(addr) : htonl(INADDR_ANY);
        skt = new Groupsock(envir(), inaddr, port, 255);
    }

    FramedSource *src;
    if (udp) {
        //src = BasicUDPSource::createNew(envir(), skt);
        src = H264VideoUDPSource::createNew(envir(), skt);
    } else {
        //src = SimpleRTPSource::createNew(envir(), skt, 96, 90000, "video/H264", 0, False);
        src = H264VideoRTPSource::createNew(envir(), skt, 96, 90000);
    }
    return H264VideoStreamFramer::createNew(envir(), src, True);
}

RTPSink *H264VideoUDPServerMediaSubsession::createNewRTPSink(
    Groupsock* rtpGroupsock, unsigned char /*rtpPayloadTypeIfDynamic*/, FramedSource */*inputSource*/)
{
    //return SimpleRTPSink::createNew(envir(), rtpGroupsock, 96, 90000, "video", "H264", 1, True, False);
    return H264VideoRTPSink::createNew(envir(), rtpGroupsock, 96);
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
