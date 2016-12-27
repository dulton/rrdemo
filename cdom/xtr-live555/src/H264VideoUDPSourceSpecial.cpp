/** \copyright The MIT License */
#include "H264VideoUDPSourceSpecial.hpp"

#include <cassert>
#include <map>
#include <set>
#include <thread>

#include <live555/Groupsock.hh>

#pragma comment(lib, "Ws2_32.lib")

#define BUFSIZE 500000

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

/// H.264 Network Abstract Layer Unit
struct nalu {
    uint32_t start_codes : 32;       // 起始码，固定为 00 00 00 01 (16)

    uint8_t forbidden_zero_bit : 1;  // 禁止位，固定为 0 (2)
    uint8_t nal_ref_idc : 2;
    uint8_t nal_unit_type : 5;       // 网络抽象层单元类型
};

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

    /* 循环内局部变量生存期优化 */
    struct timeval timeout {};
    fd_set set {};
    SOCKADDR_IN ano {};
    int anolen {sizeof ano};
    char udpack[65535] {};
    int udpacklen;

    u_int8_t buf[BUFSIZE] {};
    int buflen {0};

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

        /* 接收 UDP 数据包 */
        // SOCKADDR_IN ano {};
        // int anolen {sizeof ano};
        // char udpack[65535] {};
        // int packlen {recvfrom(skt, udpack, sizeof udpack, 0, reinterpret_cast<SOCKADDR *>(&ano), &anolen)};
        udpacklen = recvfrom(skt, udpack, sizeof udpack, 0, reinterpret_cast<SOCKADDR *>(&ano), &anolen);
        if (SOCKET_ERROR == udpacklen) {
            *env << "Error, recvfrom() failed with code " << WSAGetLastError() << ".\n";
            continue;
        }

        /* 将接收到的数据进行成帧处理 */
        if (0 < buflen && (
            0 == udpack[0] && 0 == udpack[1] && 1 == udpack[2] ||
            0 == udpack[0] && 0 == udpack[1] && 0 == udpack[2] && 1 == udpack[3]
            )) {  // 若成帧
            /* 将缓冲帧加入缓冲队列，并清理陈旧数据 */
            src->destsmtx.lock();
            for (auto dest : src->dests) {
                dest->bufsmtx.lock();
                /* 为缓冲队列创建新的缓冲 */
                auto destbuf = new buf_t;
                destbuf->data = new u_int8_t[buflen];
                /* 为缓冲赋值 */
                memcpy_s(destbuf->data, buflen, buf, buflen);
                destbuf->size = buflen;
                /* 将缓冲加入缓冲队列 */
                dest->bufs.push(destbuf);
                /* 清理缓冲队列，抛弃陈旧数据 */
                while (2 < dest->bufs.size()) {
                    *env << "A H264 video udp source buffers queue is too long, partial data has been discarded.\n";
                    delete[] dest->bufs.front()->data;
                    delete dest->bufs.front();
                    dest->bufs.pop();
                }
                dest->bufsmtx.unlock();
            }
            src->destsmtx.unlock();

            /* 重置成帧缓存 */
            memset(buf, 0, sizeof buf);
            buflen = 0;
        }

        if (buflen + udpacklen <= BUFSIZE) {
            memcpy_s(buf + buflen, BUFSIZE - buflen, udpack, udpacklen);
            buflen += udpacklen;
        } else {
            buflen += udpacklen;
            *env << "A frame size is too large, partial data has been discarded."
                << " BL/BS: " << buflen << "/" << BUFSIZE << ".\n";
        }
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
        delete[] bufs.front()->data;
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

    /* 若当前缓冲不存在，则在缓冲队列中取缓冲 */
    if (!buf) {
        bufsmtx.lock();
        buf = bufs.front();
        bufs.pop();
        bufsmtx.unlock();
        bufcur = 0;  // 重置游标
    }

    fFrameSize = buf->size < fMaxSize ? buf->size : fMaxSize;
    //if (fMaxSize < buf->size)
    //    envir() << "A frame size is too large, partial data has been discarded."
    //    << " BS/MS: " << buf->size << "/" << fMaxSize << ".\n";
    memcpy_s(fTo, fMaxSize, buf->data + bufcur, fFrameSize);

    bufcur += fFrameSize;
    buf->size -= fFrameSize;

    /* 若当前缓冲用尽，则将其销毁 */
    assert(0 <= buf->size);
    if (!buf->size) {
        delete[] buf->data;
        delete buf;
        buf = nullptr;
    }

    nextTask() = envir().taskScheduler().scheduleDelayedTask(
        0, reinterpret_cast<TaskFunc*>(afterGetting), this);
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#undef BUFSIZE
