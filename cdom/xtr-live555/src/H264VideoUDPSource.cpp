/** \copyright The MIT License */
#include "H264VideoUDPSource.hpp"

#include <cassert>

#include <map>
#include <set>
#include <thread>

#include <live555/Groupsock.hh>

#pragma comment(lib, "Ws2_32.lib")

namespace {

using rrdemo::cdom::live555::H264VideoUDPSource;

const int BUFSIZE {300000};

/// UDP 接收者类型。
struct udp_sink_t {
    u_int16_t port;    //< 收流端口。
    std::thread *thr;  //< 收流线程。
    /// 目的地集类型。
    struct dests_t {
        std::set<H264VideoUDPSource *> set;  //< 目的地集实体。
        std::mutex mtx;                      //< 目的地集锁。
        /// 判断是否为空。
        /** 检查目的地集是否为空 */
        bool empty() const { return set.empty(); }
        /// 插入目的地。
        /** 插入一个目的地。 */
        void insert(H264VideoUDPSource * const dest);
        /// 擦除目的地。
        /** 擦除一个目的地。 */
        void erase(H264VideoUDPSource * const dest);
    } dests;           //< 目的地集。
};

void udp_sink_t::dests_t::insert(H264VideoUDPSource * const dest)
{
    mtx.lock(); {
        set.insert(dest);
    } mtx.unlock();
}

void udp_sink_t::dests_t::erase(H264VideoUDPSource * const dest)
{
    mtx.lock(); {
        set.erase(dest);
    } mtx.unlock();
}

/// UDP 接收者集类型。
class UDPSinks {
public:
    /// 初始化接收者。
    /** 初始化一个 UDP 接收者。若该接收者已存在，则什么都不做。 */
    void initialize(UsageEnvironment * const env, const u_int16_t port);
    /// 寻找接收者。
    /** 寻找一个 UDP 接收者。若该接收者不存在，则返回空指针。 */
    udp_sink_t *find(const u_int16_t port);
private:
    std::map<u_int16_t, udp_sink_t *> map;  //< 接收者集实体。
    std::mutex mtx;                         //< 接收者集锁。
} gUDPSinks;  //< UDP 接收者集。

void udp_sink_thr_func(UsageEnvironment * const env, udp_sink_t * sink);
void UDPSinks::initialize(UsageEnvironment * const env, const u_int16_t port)
{
    if (map.end() != map.find(port)) return;
    auto sink = new udp_sink_t;  // leak
    sink->port = port;
    sink->thr = new std::thread(udp_sink_thr_func, env, sink);
    map.insert(std::pair<u_int16_t, udp_sink_t *>(port, sink));
}

udp_sink_t *UDPSinks::find(const u_int16_t port)
{
    if (map.end() == map.find(port)) return nullptr;
    return map[port];
}

/// UDP 接收者线程函数。
void udp_sink_thr_func(UsageEnvironment * const env, udp_sink_t * sink)
{
    /* 等待主线程初始化 */
    std::this_thread::sleep_for(std::chrono::seconds(1));

    /* WSAStartup() 由 LIVE555 管理 */

    SOCKET skt;
    /* 创建套接字 */ {
        *env << "H264VideoUDPSource: Creating socket...";
        skt = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (INVALID_SOCKET == skt) {
            *env << " error, socket() failed with error " << WSAGetLastError() << ".\n";
            WSACleanup();
            exit(EXIT_FAILURE);
        }
        *env << " done.\n";
    }

    /* 配置套接字 */ {
        *env << "H264VideoUDPSource: Setting socket option RECBUF...";
        int so_rcvbuf {1 << 24};
        if (SOCKET_ERROR == setsockopt(skt, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<const char *>(&so_rcvbuf), sizeof so_rcvbuf))
            *env << " error, setsockopt() failed with error " << WSAGetLastError() << ".\n";
        else
            *env << " done with value " << so_rcvbuf << ".\n";

        *env << "H264VideoUDPSource: Setting socket option REUSEADDR...";
        BOOL so_reuseaddr {TRUE};
        if (SOCKET_ERROR == setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char *>(&so_reuseaddr), sizeof so_reuseaddr))
            *env << " error, setsockopt() failed with error " << WSAGetLastError() << ".\n";
        else
            *env << "done with value " << (so_reuseaddr ? "ON" : "OFF") << ".\n";
    }

    /* 绑定地址 */ {
        *env << "H264VideoUDPSource: Binding address...";
        SOCKADDR_IN addr {};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(sink->port);
        if (SOCKET_ERROR == bind(skt, reinterpret_cast<PSOCKADDR>(&addr), sizeof addr)) {
            *env << " error, bind() failed with error " << WSAGetLastError() << ".\n";
            closesocket(skt);
            WSACleanup();
            exit(EXIT_FAILURE);
        }
        *env << " done with port " << ntohs(addr.sin_port) << ".\n";
    }

    /* 循环内局部变量生存期优化 */
    struct timeval timer {};
    fd_set set {};
    SOCKADDR_IN ano {};
    int anoLen {sizeof ano};
    char udpPack[65535] {};
    int udpPackLen;

    u_int8_t buf[BUFSIZE] {};
    int buflen {0};

    /* 收流与处理 */
    while (True) {
        /* 若无需求，休眠 */
        while (sink->dests.empty())
            std::this_thread::sleep_for(std::chrono::seconds(1));

        /* 重置超时时间 */
        timerclear(&timer);
        timer.tv_sec = 1;
        timer.tv_usec = 0;

        /* 检查套接字可读性 */
        FD_ZERO(&set);
        FD_SET(skt, &set);
        if (select(0, &set, nullptr, nullptr, &timer) <= 0) continue;  // 若超时
        if (!FD_ISSET(skt, &set)) continue;  // 若不可读

        /* 接收 UDP 数据包 */
        udpPackLen = recvfrom(skt, udpPack, sizeof udpPack, 0, reinterpret_cast<SOCKADDR *>(&ano), &anoLen);
        if (SOCKET_ERROR == udpPackLen) {
            *env << "H264VideoUDPSoutce: Error, recvfrom() failed with code " << WSAGetLastError() << ".\n";
            continue;
        }

        /* 将接收到的数据进行成帧处理 */
        if (0 < buflen && (
            0 == udpPack[0] && 0 == udpPack[1] && 1 == udpPack[2] ||
            0 == udpPack[0] && 0 == udpPack[1] && 0 == udpPack[2] && 1 == udpPack[3]
            )) {  // 若成帧
            /* 将缓存加入目的的缓存队列，并为其清理陈旧数据 */
            sink->dests.mtx.lock();
            for (auto dest : sink->dests.set) {
                H264VideoUDPSource::Buf *destbuf;
                while (nullptr == (destbuf = dest->bufs.allocateforce()))
                    std::this_thread::sleep_for(std::chrono::microseconds(100));
                size_t discarded;
                if (0 != (discarded = destbuf->cpyf(buf, buflen)))
                    *env << "H264VideoUDPSource: A frame size is too large, "
                    << discarded << " bytes data has been discarded.";
                dest->bufs.push(destbuf);
            }
            sink->dests.mtx.unlock();

            /* 重置成帧缓存 */
            memset(buf, 0, sizeof buf);
            buflen = 0;
        }

        if (buflen + udpPackLen <= BUFSIZE) {
            memcpy_s(buf + buflen, BUFSIZE - buflen, udpPack, udpPackLen);
            buflen += udpPackLen;
        } else {
            buflen += udpPackLen;
            *env << "H264VideoUDPSource: A frame size is too large, partial data has been discarded."
                << " BL/BS: " << buflen << "/" << BUFSIZE << ".\n";
        }
    }

    /* 关闭套接字 */ {
        *env << "Close socket...";
        closesocket(skt);
        *env << "done.\n";
    }

    /* WSACleanup() 由 LIVE555 管理 */

    *env << "\n";
}

}// namespace

namespace rrdemo {
namespace cdom {
namespace live555 {

H264VideoUDPSource::H264VideoUDPSource(
    UsageEnvironment &env, Groupsock *skt, unsigned pfs, unsigned ptpf) :
    FramedSource(env), skt {skt}
{
    auto sink = gUDPSinks.find(ntohs(skt->port().num()));
    assert(sink);
    sink->dests.insert(this);
}

H264VideoUDPSource::~H264VideoUDPSource()
{
    auto sink = gUDPSinks.find(ntohs(skt->port().num()));
    assert(sink);
    sink->dests.erase(this);
}

void H264VideoUDPSource::doGetNextFrame()
{
    /* 若当前处理缓存为空，则在缓存池中取缓存 */
    if (nullptr == curb)
        while (nullptr == (curb = bufs.pop()))
            std::this_thread::sleep_for(std::chrono::microseconds(100));

    //envir() << "data: " << bufs.datalen()
    //    << ", idle: " << bufs.idlelen()
    //    << ", curlen: " << curb->len() << ".\n";

    /* 将当前处理缓存中的数据，按指定量，剪切到指定位置 */
    fFrameSize = curb->len() < fMaxSize ? curb->len() : fMaxSize;
    curb->cutt(fTo, fMaxSize, fFrameSize);

    /* 若当前处理缓存处理完毕，则将其回收 */
    if (curb->empty()) {
        bufs.recycle(curb);
        curb = nullptr;
    }

    /* 事件循环 */
    nextTask() = envir().taskScheduler().scheduleDelayedTask(
        0, reinterpret_cast<TaskFunc*>(afterGetting), this);
}

void H264VideoUDPSource::initializeSourceBeforeEventLoop(UsageEnvironment *env, u_int16_t port)
{
    gUDPSinks.initialize(env, port);
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
