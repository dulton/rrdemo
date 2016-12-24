/** \file
 *  \author zhengrr
 *  \date 2016-12-15 – 22
 *  \copyright The MIT License
 */
#include <cstdint>

#include <live555/BasicUsageEnvironment.hh>
#include <live555/liveMedia.hh>

#include "h264_video_udp_server_media_subsession.hpp"

namespace {
int Main(int, char *[])
{
    using rrdemo::cdom::live555::H264VideoUDPServerMediaSubsession;

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

    /* MPEG-2 TS UDP */
    {
        ServerMediaSession *sms {
            ServerMediaSession::createNew(*env, "mpeg2tsudp", "info", "desc")};
        sms->addSubsession(MPEG2TransportUDPServerMediaSubsession
                           ::createNew(*env, "127.0.0.1", 10096, False));
        server->addServerMediaSession(sms);
        *env << server->rtspURL(sms) << "\n";
    }

    /* MPEG-2 TS RTP */
    {
        ServerMediaSession *sms {
            ServerMediaSession::createNew(*env, "mpeg2tsrtp", "info", "desc")};
        sms->addSubsession(MPEG2TransportUDPServerMediaSubsession
                           ::createNew(*env, "127.0.0.1", 5504, True));
        server->addServerMediaSession(sms);
        *env << server->rtspURL(sms) << "\n";
    }

    /* H.264 ES (V) */
    {
        ServerMediaSession *sms {
            ServerMediaSession::createNew(*env, "h264", "info", "desc")};
        OutPacketBuffer::maxSize = 100000;
        sms->addSubsession(H264VideoFileServerMediaSubsession
                           ::createNew(*env, "rec.h264", False));
        server->addServerMediaSession(sms);
        *env << server->rtspURL(sms) << "\n";
    }

    /* H.264 ES (V) UDP */
    {
        ServerMediaSession *sms {
            ServerMediaSession::createNew(*env, "h264udp", "info", "desc")};
        sms->addSubsession(H264VideoUDPServerMediaSubsession
                           ::createNew(*env, "127.0.0.1", 10096, True));
        server->addServerMediaSession(sms);
        *env << server->rtspURL(sms) << "\n";
    }

    /* H.264 ES (V) RTP */
    {
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
