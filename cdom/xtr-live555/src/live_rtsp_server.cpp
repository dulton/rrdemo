/** \file
 *  \author zhengrr
 *  \date 2016-12-15 – 27
 *  \copyright The MIT License
 */
#include <live555/BasicUsageEnvironment.hh>
#include <live555/liveMedia.hh>

#include "H264VideoUDPServerMediaSubsession.hpp"
#include "H264VideoUDPSource.hpp"

namespace {
int Main(int, char *[])
{
    using rrdemo::cdom::live555::H264VideoUDPServerMediaSubsession;
    using rrdemo::cdom::live555::H264VideoUDPSource;

    /* 创建任务调度器与使用环境 */
    TaskScheduler *schr {BasicTaskScheduler::createNew()};
    UsageEnvironment *env = BasicUsageEnvironment::createNew(*schr);

    /* 创建实时串流协议服务器 */
    RTSPServer *server {RTSPServer::createNew(*env)};
    if (nullptr == server) {
        *env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
        return EXIT_FAILURE;
    }
    *env << "ZHENGRR'S RTSP SERVER\n";
    *env << server->rtspURLPrefix() << "<stream name>\n";
    *env << "\n";

    *env << "Stream List:\n";

    /* H.264 ES (V) UDP */ {
        ServerMediaSession *sms {
            ServerMediaSession::createNew(*env, "h264udp", "info", "desc")};
        OutPacketBuffer::maxSize = 300000;
        H264VideoUDPSource::initializeSourceBeforeEventLoop(env, 10096);
        sms->addSubsession(H264VideoUDPServerMediaSubsession
                           ::createNew(*env, "127.0.0.1", 10096, True));
        server->addServerMediaSession(sms);
        *env << server->rtspURL(sms) << "\n";
    }

    /* H.264 ES (V) RTP */ {
        ServerMediaSession *sms {
            ServerMediaSession::createNew(*env, "h264rtp", "info", "desc")};
        sms->addSubsession(H264VideoUDPServerMediaSubsession
                           ::createNew(*env, "127.0.0.1", 5004, False));
        server->addServerMediaSession(sms);
        *env << server->rtspURL(sms) << "\n";
    }

    *env << "\n";

    /* 启用事件循环 */
    env->taskScheduler().doEventLoop();// noreturn
    return EXIT_SUCCESS;
}
}

#ifndef ENTRY_SWITCH
int main(int argc, char *argv[]) { return Main(argc, argv); }
#endif// ENTRY SWITCH
