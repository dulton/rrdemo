/** \copyright The MIT License */
#include "h264_video_udp_source_special.hpp"

#include <cassert>
#include <map>
#include <set>
#include <thread>

#include <live555/Groupsock.hh>

#pragma comment(lib, "Ws2_32.lib")

namespace {

using rrdemo::cdom::live555::H264VideoUdpSourceSpecial;
using rrdemo::cdom::live555::buf_t;

struct src_t {
    u_int16_t port;
    std::thread *thr;                             //< 收流线程。
    std::set<H264VideoUdpSourceSpecial *> dests;  //< 缓冲存储处集。
    std::mutex destsmtx;                          //< 缓冲存储处集锁。
};

std::map<u_int16_t, src_t *> srcs;  //< 源集。

void sink(UsageEnvironment * const env, src_t * const src)
{
    /* 等待主线程初始化 */
    std::this_thread::sleep_for(std::chrono::seconds(1));

    /* WSAStartup() 由 LIVE555 管理 */
    *env << "Startuping windows socket...";
    WSADATA data;
    int rwsas {WSAStartup(MAKEWORD(2, 2), &data)};  // Result of WSAStartup
    if (NO_ERROR != rwsas) {
        *env << " error, WSAStartup() failed with error " << rwsas << ".\n";
        exit(EXIT_FAILURE);
    }
    *env << " done.\n";


    /* 创建套接字 */
    *env << "Creating socket...";
    SOCKET skt {socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)};
    if (INVALID_SOCKET == skt) {
        *env << " error, socket() failed with error " << WSAGetLastError() << ".\n";
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    *env << " done.\n";

    /* 配置套接字 */
    *env << "Setting socket option RECBUF...";
    int so_rcvbuf {1 << 24};
    if (SOCKET_ERROR == setsockopt(skt, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<const char *>(&so_rcvbuf), sizeof so_rcvbuf))
        *env << " error, setsockopt() failed with error " << WSAGetLastError() << ".\n";
    else
        *env << " done with SO_RECBUF " << so_rcvbuf << ".\n";

    *env << "Setting socket option REUSEADDR...";
    BOOL so_reuseaddr {TRUE};
    if (SOCKET_ERROR == setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char *>(&so_reuseaddr), sizeof so_reuseaddr))
        *env << " error, setsockopt() failed with error " << WSAGetLastError() << ".\n";
    else
        *env << "done with SO_REUSEADDR " << (so_reuseaddr ? "ON" : "OFF") << ".\n";

    /* 绑定地址 */
    *env << "Binding address...";
    SOCKADDR_IN addr {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(src->port);
    if (SOCKET_ERROR == bind(skt, reinterpret_cast<PSOCKADDR>(&addr), sizeof addr)) {
        *env << " error, bind() failed with error " << WSAGetLastError() << ".\n";
        closesocket(skt);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    *env << " done with port " << ntohs(addr.sin_port) << ".\n";

    /* 循环局部变量生存期优化 */
    struct timeval timeout {};
    fd_set set {};
    SOCKADDR_IN ano {};
    int anolen {sizeof ano};
    char buf[300000] {};
    int datalen;

    /* 收流与处理 */
    while (True) {
        /* 若无需求，休眠 */
        while (src->dests.size() <= 0)
            std::this_thread::sleep_for(std::chrono::seconds(1));

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
            *env << "Error, recvfrom() failed with code " << WSAGetLastError() << ".\n";
            continue;
        }

        /* 将接收到的数据进行成帧处理，并分发给各存储处 */
        src->destsmtx.lock();
        for (auto dest : src->dests) {
            dest->bufsmtx.lock();
            auto destbuf = new buf_t;
            memcpy_s(destbuf->data, sizeof destbuf->data, buf, datalen);
            destbuf->size = datalen;
            dest->bufs.push(destbuf);
            /* 抛弃陈旧数据 */
            while (3 < dest->bufs.size()) {
                *env << "A H264 video udp source buffer is too long, partial data has been discarded.";
                delete dest->bufs.front();
                dest->bufs.pop();
            }
            dest->bufsmtx.unlock();
        }
        src->destsmtx.unlock();
    }

    /* 关闭套接字 */
    *env << "Close socket...";
    closesocket(skt);
    *env << "done.\n";

    /* WSACleanup() 由 LIVE555 管理 */

    *env << "\n";
}

/// 将缓冲存储处注册到源中。
void regis(H264VideoUdpSourceSpecial * const obj, u_int16_t port)
{
    assert(srcs.end() != srcs.find(port));
    srcs[port]->destsmtx.lock();
    srcs[port]->dests.insert(obj);
    srcs[port]->destsmtx.unlock();
}

/// 将缓冲存储处从源中取消注册。
void unreg(H264VideoUdpSourceSpecial * const obj, u_int16_t port)
{
    assert(srcs.end() != srcs.find(port));
    srcs[port]->destsmtx.lock();
    srcs[port]->dests.erase(obj);
    srcs[port]->destsmtx.unlock();
}

}// namespace

namespace rrdemo {
namespace cdom {
namespace live555 {

void H264VideoUdpSourceSpecial::initializeSource(UsageEnvironment *env, u_int16_t port)
{
    if (srcs.end() != srcs.find(port)) return;

    auto src = new src_t;  // leak
    src->port = port;
    src->thr = new std::thread(sink, env, src);
    srcs.insert(std::pair<u_int16_t, src_t *>(port, src));
}

H264VideoUdpSourceSpecial *H264VideoUdpSourceSpecial::createNew(
    UsageEnvironment &env, Groupsock *skt, unsigned pfs, unsigned ptpf)
{
    return new H264VideoUdpSourceSpecial(env, skt, pfs, ptpf);
}

H264VideoUdpSourceSpecial::H264VideoUdpSourceSpecial(
    UsageEnvironment &env, Groupsock *skt, unsigned pfs, unsigned ptpf) :
    FramedSource(env), skt {skt}
{
    regis(this, ntohs(skt->port().num()));
}

H264VideoUdpSourceSpecial::~H264VideoUdpSourceSpecial()
{
    unreg(this, ntohs(skt->port().num()));
    bufsmtx.lock();
    while (!bufs.empty()) {
        delete bufs.front();
        bufs.pop();
    }
    bufsmtx.unlock();
}

void H264VideoUdpSourceSpecial::doGetNextFrame()
{
    while (bufs.empty()) {
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }

    bufsmtx.lock();
    auto buf = bufs.front();
    fFrameSize = buf->size < fMaxSize ? buf->size : fMaxSize;
    memcpy_s(fTo, fMaxSize, buf->data, fFrameSize);
    delete buf;
    bufs.pop();
    bufsmtx.unlock();

    nextTask() = envir().taskScheduler().scheduleDelayedTask(
        0, reinterpret_cast<TaskFunc*>(afterGetting), this);
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
