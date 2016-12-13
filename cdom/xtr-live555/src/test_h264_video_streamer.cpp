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

void Play();
void AfterPlaying(void *);

UsageEnvironment *env {nullptr};
H264VideoStreamFramer *VideoSource {nullptr};
RTPSink *VideoSink {nullptr};

int Main(int, char *[])
{
    /* 创建任务调度器与使用环境 */
    TaskScheduler *schr {BasicTaskScheduler::createNew()};
    env = BasicUsageEnvironment::createNew(*schr);

    /* 分配四版网际协议组播地址、创建实时传输协议及其控制协议的组播套接字 */
    struct in_addr destAddr;
    destAddr.s_addr = chooseRandomIPv4SSMAddress(*env);
    Groupsock rtpGrpSkt(*env, destAddr, /* 端口 */18888, /* 存活跳数 */255);
    rtpGrpSkt.multicastSendOnly();
    Groupsock rtcpGrpSkt(*env, destAddr, 18889, 255);
    rtcpGrpSkt.multicastSendOnly();

    /* 创建实时传输协议高级视频编码视频接收器及配套的控制协议实例 */
    OutPacketBuffer::maxSize = 100000;
    VideoSink = H264VideoRTPSink::createNew(*env, &rtpGrpSkt, 96);
    const unsigned maxCNAMElen = 100;
    unsigned char CNAME[maxCNAMElen + 1];
    gethostname((char*)CNAME, maxCNAMElen);
    CNAME[maxCNAMElen] = '\0';
    RTCPInstance *rtcp {
        RTCPInstance::createNew(*env, &rtcpGrpSkt,
        /*预估带宽 */500/*kbps*/, CNAME, VideoSink, nullptr, /*源特定组播源 */True)};

    RTSPServer *rtspServer;
    if (!((rtspServer = RTSPServer::createNew(*env, 8554)))) {
        *env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
        return EXIT_FAILURE;
    }
    ServerMediaSession *sms {
        ServerMediaSession::createNew(*env, "testStream", INPUT_FILE_NAME,
        "Session streamed by \"testH264VideoStreamer\"", /*源特定组播 */True)};
    sms->addSubsession(PassiveServerMediaSubsession::createNew(*VideoSink, rtcp));
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

    VideoSource = H264VideoStreamFramer::createNew(*env, static_cast<FramedSource *>(fileSource));

    *env << "Beginning to read from file...\n";
    VideoSink->startPlaying(*VideoSource, AfterPlaying, VideoSink);
}

void AfterPlaying(void *)
{
    *env << "...done reading from file\n";
    VideoSink->stopPlaying();
    Medium::close(VideoSource);

    Play();
}

}// namespace

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[]) { return Main(argc, argv); }
#endif// ENTRY SWITCH
