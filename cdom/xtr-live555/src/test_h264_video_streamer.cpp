/** \file
 *  \author zhengrr
 *  \date 2016-12-12
 *  \copyright The MIT License
 */
#include <live555/BasicUsageEnvironment.hh>
#include <live555/GroupsockHelper.hh>
#include <live555/liveMedia.hh>

namespace {

const char const *INPUT_FILE_NAME {"test.264"};
const portNumBits RTP_PORT_NUM {18888};
const portNumBits RTCP_PORT_NUM {RTP_PORT_NUM + 1};
const u_int8_t TTL {255};

void Play();
void AfterPlaying(void *);

UsageEnvironment *env {nullptr};
H264VideoStreamFramer *videoSource {nullptr};
RTPSink *videoSink {nullptr};

int Main(int, char *[])
{
    TaskScheduler* scheduler {BasicTaskScheduler::createNew()};
    env = BasicUsageEnvironment::createNew(*scheduler);

    struct in_addr destAddr;
    destAddr.s_addr = chooseRandomIPv4SSMAddress(*env);
    const Port rtpPort(RTP_PORT_NUM);
    const Port rtcpPort(RTCP_PORT_NUM);

    Groupsock rtpGroupsock(*env, destAddr, rtpPort, TTL);
    rtpGroupsock.multicastSendOnly();
    Groupsock rtcpGroupsock(*env, destAddr, rtcpPort, TTL);
    rtcpGroupsock.multicastSendOnly();

    OutPacketBuffer::maxSize = 100000;
    videoSink = H264VideoRTPSink::createNew(*env, &rtpGroupsock, 96);

    const unsigned estimatedSessionBandwidth = 500;
    const unsigned maxCNAMElen = 100;
    unsigned char CNAME[maxCNAMElen + 1];
    gethostname((char*)CNAME, maxCNAMElen);
    CNAME[maxCNAMElen] = '\0';
    RTCPInstance *rtcp {
        RTCPInstance::createNew(*env, &rtcpGroupsock,
        estimatedSessionBandwidth, CNAME, videoSink, nullptr, True)};

    RTSPServer *rtspServer;
    if (!((rtspServer = RTSPServer::createNew(*env, 8554)))) {
        *env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
        return EXIT_FAILURE;
    }
    ServerMediaSession *sms {
        ServerMediaSession::createNew(*env, "testStream", INPUT_FILE_NAME,
        "Session streamed by \"testH264VideoStreamer\"", True)};
    sms->addSubsession(PassiveServerMediaSubsession::createNew(*videoSink, rtcp));
    rtspServer->addServerMediaSession(sms);

    char *url {rtspServer->rtspURL(sms)};
    *env << "Play this stream using the URL \"" << url << "\"\n";
    delete[] url;

    // Start the streaming:
    *env << "Beginning streaming...\n";
    Play();

    env->taskScheduler().doEventLoop();// noreturn

    return EXIT_SUCCESS;
}

void Play()
{
    ByteStreamFileSource *fileSource;
    if (!((fileSource = ByteStreamFileSource::createNew(*env, INPUT_FILE_NAME)))) {
        *env << "Unable to open file \"" << INPUT_FILE_NAME << "\" as a byte-stream file source\n";
        exit(EXIT_FAILURE);
    }

    videoSource = H264VideoStreamFramer::createNew(*env, static_cast<FramedSource *>(fileSource));

    *env << "Beginning to read from file...\n";
    videoSink->startPlaying(*videoSource, AfterPlaying, videoSink);
}

void AfterPlaying(void */*clientData*/)
{
    *env << "...done reading from file\n";
    videoSink->stopPlaying();
    Medium::close(videoSource);

    Play();
}

}// namespace

#ifndef ENTRY_SWITCH
int main(int argc, char *argv[]) { return Main(argc, argv); }
#endif// ENTRY SWITCH
