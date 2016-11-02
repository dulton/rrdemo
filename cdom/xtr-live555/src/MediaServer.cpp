/** \file
 *  \author zhengrr
 *  \date 2016-11-2
 *  \copyright The MIT License
 */
#include <live555/BasicUsageEnvironment.hh>
#include "RTSPServer.hpp"

int main(int argc, char** argv) {
    // 创建调度器, 环境, 与认证数据:
    TaskScheduler* scheduler = BasicTaskScheduler::createNew();
    UsageEnvironment* env = BasicUsageEnvironment::createNew(*scheduler);

    auto authDB = new UserAuthenticationDatabase;
    authDB->addUserRecord("UsErNaMe", "PaSsWoRd");

    // 创建 RTSP 服务器:
    portNumBits rtspServerPortNum = 554;
    RTSPServer* rtspServer = rrdemo::cdom::live555::RTSPServer::createNew(
        *env, rtspServerPortNum, authDB);
    if (!rtspServer) {
        rtspServerPortNum = 8554;
        rtspServer = rrdemo::cdom::live555::RTSPServer::createNew(
            *env, rtspServerPortNum, authDB);
    }
    if (!rtspServer) {
        *env << "Failed to create RTSP server: " <<
            env->getResultMsg() << "\n";
        exit(1);
    }

    // 启动事件循环, 此函数为 noreturn 函数:
    env->taskScheduler().doEventLoop();

    return 0;
}
