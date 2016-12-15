/** \file
 *  \author zhengrr
 *  \date 2016-12-15
 *  \copyright The MIT License
 */
#include <live555/BasicUsageEnvironment.hh>
#include <live555/liveMedia.hh>

#include "h264_video_udp_server_media_subsession.hpp"

namespace {
int Main(int argc, char *argv[])
{
    /* 创建任务调度器与使用环境 */
    TaskScheduler *schr {BasicTaskScheduler::createNew()};
    UsageEnvironment *env = BasicUsageEnvironment::createNew(*schr);

    /* 创建实时串流协议服务器 */
    RTSPServer *server {RTSPServer::createNew(*env, 554)};
    if (!server) return -1;

    /* H.264 ES (V) */
    {
        ServerMediaSession *sms {
            ServerMediaSession::createNew(*env, "REC", "info", "desc")};
        OutPacketBuffer::maxSize = 100000;
        sms->addSubsession(H264VideoFileServerMediaSubsession
                           ::createNew(*env, "rec.264", False));
        server->addServerMediaSession(sms);
    }

    /* H.264 ES (V) UDP */
    {
        ServerMediaSession *sms {
            ServerMediaSession::createNew(*env, "LIVE", "info", "desc")};
        sms->addSubsession(H264VideoUDPServerMediaSubsession
                           ::createNew(*env, "127.0.0.1", 10004, True));
        server->addServerMediaSession(sms);
    }

    /* 启用事件循环 */
    env->taskScheduler().doEventLoop();// noreturn
    return EXIT_SUCCESS;
}
}

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[]) { return Main(argc, argv); }
#endif// ENTRY SWITCH
