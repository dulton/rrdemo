/** \copyright The MIT License */
#include "H264VideoUDPSource.hpp"

#include <live555/Groupsock.hh>

#pragma comment(lib, "Ws2_32.lib")

namespace rrdemo {
namespace cdom {
namespace live555 {

#ifdef CODING

H264VideoUdpSource *H264VideoUdpSource::createNew(
    UsageEnvironment &env, Groupsock *skt, unsigned pfs, unsigned ptpf)
{
    return new H264VideoUdpSource(env, skt, pfs, ptpf);
}

H264VideoUdpSource::H264VideoUdpSource(
    UsageEnvironment &env, Groupsock *skt, unsigned pfs, unsigned ptpf) :
    FramedSource(env), port {skt->port()}
{
    sinkloop = true;
    sinkthr = new std::thread([this]() {sinkthrfunc(); });
}

H264VideoUdpSource::~H264VideoUdpSource()
{
    //TODO: leak! bufs 尚未清空。
    sinkloop = false;
    sinkthr->join();
    delete sinkthr;
}

void H264VideoUdpSource::doGetNextFrame()
{
    while (bufsque.empty()) {
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }

    quemtx.lock();
    {
        auto buf = bufsque.front();

        fFrameSize = fMaxSize < buf->size ? fMaxSize : buf->size;
        memcpy_s(fTo, fMaxSize, buf->data, fFrameSize);

        bufsque.pop();
        delete buf;
    }
    quemtx.unlock();

    nextTask() = envir().taskScheduler().scheduleDelayedTask(
        0, reinterpret_cast<TaskFunc*>(afterGetting), this);
}

void H264VideoUdpSource::sinkthrfunc()
{
    /* 防止瞬间构造又析构对象 */
    std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    if (!sinkloop) return;

    /* WSAStartup() 由 LIVE555 管理 */
    envir() << "Startuping windows socket...";
    WSADATA data;
    int rwsas {WSAStartup(MAKEWORD(2, 2), &data)};  // Result of WSAStartup
    if (NO_ERROR != rwsas) {
        envir() << " error, WSAStartup() failed with error " << rwsas << ".\n";
        exit(EXIT_FAILURE);
    }
    envir() << " done.\n";


    /* 创建套接字 */
    envir() << "Creating socket...";
    SOCKET skt {socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)};
    if (INVALID_SOCKET == skt) {
        envir() << " error, socket() failed with error " << WSAGetLastError() << ".\n";
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    envir() << " done.\n";

    /* 配置套接字 */
    envir() << "Setting socket option RECBUF...";
    int so_rcvbuf {1 << 24};
    if (SOCKET_ERROR == setsockopt(skt, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<const char *>(&so_rcvbuf), sizeof so_rcvbuf))
        envir() << " error, setsockopt() failed with error " << WSAGetLastError() << ".\n";
    else
        envir() << " done with SO_RECBUF " << so_rcvbuf << ".\n";

    envir() << "Setting socket option REUSEADDR...";
    BOOL so_reuseaddr {TRUE};
    if (SOCKET_ERROR == setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char *>(&so_reuseaddr), sizeof so_reuseaddr))
        envir() << " error, setsockopt() failed with error " << WSAGetLastError() << ".\n";
    else
        envir() << "done with SO_REUSEADDR " << (so_reuseaddr ? "ON" : "OFF") << ".\n";

    /* 绑定地址 */
    envir() << "Binding address...";
    SOCKADDR_IN addr {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = port.num();  // 已是 net-style
    if (SOCKET_ERROR == bind(skt, reinterpret_cast<PSOCKADDR>(&addr), sizeof addr)) {
        envir() << " error, bind() failed with error " << WSAGetLastError() << ".\n";
        closesocket(skt);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    envir() << " done with port " << ntohs(addr.sin_port) << ".\n";

    /* 循环局部变量生存期优化 */
    struct timeval timeout {};
    fd_set set {};
    SOCKADDR_IN ano {};
    int anolen {sizeof ano};
    char buf[300000] {};
    int datalen;

    /* 收流与处理 */
    while (sinkloop) {
        envir() << ".";
        /* 重置超时时间 */
        // struct timeval timeout {};
        timerclear(&timeout);
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        /* 检查套接字可读性 */
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
            envir() << "\nError, recvfrom() failed with code " << WSAGetLastError() << ".\n";
            continue;
        }
        envir() << "\nBytes received: " << datalen << ".\n";

        quemtx.lock();
        {
            auto quebuf = new buf_t;

            memcpy_s(quebuf->data, sizeof quebuf->data, buf, datalen);
            quebuf->size = datalen;

            bufsque.push(quebuf);
        }
        quemtx.unlock();
    }

    /* 关闭套接字 */
    envir() << "Close socket...";
    closesocket(skt);
    envir() << "done.\n";

    /* WSACleanup() 由 LIVE555 管理 */

    envir() << "\n";
}

#endif// CODING

}// namespace live555
}// namespace cdom
}// namespace rrdemo
