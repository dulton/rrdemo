/** \file
 *  \author zhengrr
 *  \date 2016-11-2 – 12-9
 *  \copyright The MIT License
 */
#include <live555/BasicUsageEnvironment.hh>
#include "rtsp_server.hpp"

namespace {
int Main(int, char *[])
{
    using MyRTSPServer = rrdemo::cdom::live555::RTSPServer;

    // 创建调度器、环境、认证数据
    TaskScheduler *scheduler {BasicTaskScheduler::createNew()};
    UsageEnvironment *env {BasicUsageEnvironment::createNew(*scheduler)};

    UserAuthenticationDatabase *authDB {new UserAuthenticationDatabase};
    authDB->addUserRecord("username", "password");

    // 创建 RTSP 服务器
    if (MyRTSPServer::createNew(*env, 554, authDB)) {
        *env << "Bind port 554.\n";
    } else if (MyRTSPServer::createNew(*env, 8554, authDB)) {
        *env << "Bind port 8554.\n";
    } else {
        *env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
        return EXIT_FAILURE;
    }

    // 启用事件循环
    env->taskScheduler().doEventLoop();// noreturn

    return EXIT_SUCCESS;
}
}// namespace

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[]) { return Main(argc, argv); }
#endif// ENTRY SWITCH
