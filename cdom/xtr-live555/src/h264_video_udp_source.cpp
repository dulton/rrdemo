/** \copyright The MIT License */
#include "h264_video_udp_source.hpp"

#include <live555/Groupsock.hh>

namespace rrdemo {
namespace cdom {
namespace live555 {

H264VideoUdpSource *H264VideoUdpSource::createNew(
    UsageEnvironment &env, Groupsock *skt, unsigned pfs, unsigned ptpf)
{
    return new H264VideoUdpSource(env, skt, pfs, ptpf);
}

H264VideoUdpSource::H264VideoUdpSource(
    UsageEnvironment &env, Groupsock *skt, unsigned pfs, unsigned ptpf) :
    FramedSource(env), port {skt->port()}
{
    for (auto buf : bufs)
        idleque.push(buf);

    sinkloop = true;
    sinkthr = new std::thread([](H264VideoUdpSource * const obj) {

        // WSAStartup() 由 LIVE555 管理。

        // 创建套接字：
        obj->envir() << "Creating Socket...";
        SOCKET skt {socket(AF_INET, SOCK_DGRAM, 0)};
        if (INVALID_SOCKET == skt) {
            obj->envir() << " ! socket() failed with error " << WSAGetLastError() << ".\n";
            WSACleanup();
            exit(EXIT_FAILURE);
        }
        int sorcvbuf {1 << 24};
        setsockopt(skt, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<const char *>(&sorcvbuf), sizeof sorcvbuf);
        obj->envir() << " Created.\n";

        // 绑定地址：
        obj->envir() << "Binding address...";
        SOCKADDR_IN addr {};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = obj->port.num();  // 已是 net-style
        if (SOCKET_ERROR == bind(skt, reinterpret_cast<SOCKADDR *>(&addr), sizeof addr)) {
            obj->envir() << " ! bind() failed with error " << WSAGetLastError() << ".\n";
            closesocket(skt);
            WSACleanup();
            exit(EXIT_FAILURE);
        }
        obj->envir() << " Binded with port " << ntohs(addr.sin_port) << ".\n";

        // 循环局部变量生存期优化：
        struct timeval timeout {};
        fd_set set {};
        SOCKADDR_IN ano {};
        int anolen {sizeof ano};
        char buf[300000] {};
        int datalen;

        while (obj->sinkloop) {
            // 重置超时时间：
            // struct timeval timeout {};
            ZeroMemory(&timeout, sizeof timeout);
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;

            // 检查套接字可读性：
            // fd_set set {};
            FD_ZERO(&set);
            FD_SET(skt, &set);
            if (select(0, &set, nullptr, nullptr, &timeout) <= 0) continue;  // 若超时
            if (!FD_ISSET(skt, &set)) continue;  // 若不可读

            // SOCKADDR_IN ano {};
            // int anolen {sizeof ano};
            // char buf[300000] {};
            // int datalen {recvfrom(skt, buf, sizeof buf, 0, reinterpret_cast<SOCKADDR *>(&ano), &anolen)};
            datalen = recvfrom(skt, buf, sizeof buf, 0, reinterpret_cast<SOCKADDR *>(&ano), &anolen);
            if (SOCKET_ERROR == datalen || datalen <= 0) {
                obj->envir() << "! recvfrom() failed with code " << WSAGetLastError() << ".\n";
                continue;
            }
            obj->envir() << "Bytes received: " << datalen << ".\n";

            obj->quemtx.lock();
            if (!obj->idleque.empty()) {
                auto &quebuf = obj->idleque.front();
                obj->idleque.pop();

                memcpy_s(quebuf.data, 300000, buf, datalen);
                quebuf.size = datalen;

                obj->dataque.push(quebuf);
            } else {
                auto &quebuf = obj->dataque.front();
                obj->dataque.pop();

                memcpy_s(quebuf.data, 300000, buf, datalen);
                quebuf.size = datalen;

                obj->dataque.push(quebuf);
            }
            obj->quemtx.unlock();
        }

        closesocket(skt);

        // WSACleanup() 由 LIVE555 管理。

    }, this);
}

H264VideoUdpSource::~H264VideoUdpSource()
{
    sinkloop = false;
    sinkthr->join();
    delete sinkthr;
}

void H264VideoUdpSource::doGetNextFrame()
{
    while (dataque.empty()) {
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }

    quemtx.lock();
    {
        auto &buf = dataque.front();
        fFrameSize = fMaxSize < buf.size ? fMaxSize : buf.size;
        memcpy_s(fTo, fMaxSize, buf.data, fFrameSize);
        dataque.pop();

        buf.size = 0;

        idleque.push(buf);
    }
    quemtx.unlock();

    nextTask() = envir().taskScheduler().scheduleDelayedTask(
        0, reinterpret_cast<TaskFunc*>(afterGetting), this);
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
