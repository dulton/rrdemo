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

/// 接收者类型。
struct sink_t {
    u_int16_t port;    //< 收流端口。
    std::thread *thr;  //< 收流线程。
    /// 目的地集类型。
    struct dests_t {
        std::set<H264VideoUDPSource *> set;  //< 目的地集实体。
        std::mutex mtx;                      //< 目的地集锁。
        /// 判断目的地集是否为空。
        bool empty() const { return set.empty(); }
        /// 插入目的地。
        void insert(H264VideoUDPSource * const dest);
        /// 擦除目的地。
        void erase(H264VideoUDPSource * const dest);
    } dests;           //< 目的地集。
};

void sink_t::dests_t::insert(H264VideoUDPSource * const dest)
{
    mtx.lock(); {
        set.insert(dest);
    } mtx.unlock();
}

void sink_t::dests_t::erase(H264VideoUDPSource * const dest)
{
    mtx.lock(); {
        set.erase(dest);
    } mtx.unlock();
}

/// 接收者集类。
class Sinks {
public:
    /// 申请接收者.
    void apply(UsageEnvironment * const env, const u_int16_t port);
    /// 寻找接收者。
    sink_t *find(const u_int16_t port);
private:
    std::map<u_int16_t, sink_t *> map;  //< 接收者集实体。
    std::mutex mtx;                     //< 接收者集锁。
} gSinks;  //< 接收者集。

void sink_thr_func(UsageEnvironment * const env, sink_t * sink);
void Sinks::apply(UsageEnvironment * const env, const u_int16_t port)
{
    if (map.end() != map.find(port)) return;
    auto sink = new sink_t;  // leak
    sink->port = port;
    sink->thr = new std::thread(sink_thr_func, env, sink);
    map.insert(std::pair<u_int16_t, sink_t *>(port, sink));
}

sink_t *Sinks::find(const u_int16_t port)
{
    if (map.end() == map.find(port)) return nullptr;
    return map[port];
}

/// 用户数据报协议接收者线程函数。
void sink_thr_func(UsageEnvironment * const env, sink_t * sink)
{
    /* 等待主线程初始化 */
    std::this_thread::sleep_for(std::chrono::seconds(1));

    /* Windows Socket 的启用和关闭由 LIVE555 管理 */

    SOCKET skt;  //< SocKeT。
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

    SOCKADDR_IN raddr {};  //< Receiver ADDRess
    /* 绑定地址 */ {
        *env << "H264VideoUDPSource: Binding address...";
        raddr.sin_family = AF_INET;
        raddr.sin_addr.s_addr = htonl(INADDR_ANY);
        raddr.sin_port = htons(sink->port);
        if (SOCKET_ERROR == bind(skt, reinterpret_cast<PSOCKADDR>(&raddr), sizeof raddr)) {
            *env << " error, bind() failed with error " << WSAGetLastError() << ".\n";
            closesocket(skt);
            WSACleanup();
            exit(EXIT_FAILURE);
        }
        *env << " done with port " << ntohs(raddr.sin_port) << ".\n";
    }

    /* 循环内局部变量生存期优化 */
    TIMEVAL timer {};
    FD_SET set {};
    SOCKADDR_IN saddr {};              //< Sender ADDRess。
    int saddrl {sizeof saddr};         //< Sender SocKeT Length。
    static const size_t PCKS {65535};  //< udp PaCKet Size。
    char pck[PCKS] {};                 //< udp PaCKet。
    size_t pckl;                       //< udp PaCKet Length。
    size_t discarded;                  //< 丢弃的字节数。
    size_t actual;                     //< 使用的字节数。

    // H.264 网络抽象层单元缓存（Network Abstraction Layer Unit Buffer）
    static const size_t NALUBS {300000};  //< NALUB Size。
    u_int8_t nalub[NALUBS] {};            //< NALUB。
    size_t nalubl {};                     //< NALUB Length。
    int nalufc {};                        //< NALU Flag Check

    /* 收流与处理 */
    while (True) {
        /* 若当前无需求，休眠一段时间，等待需求 */
        while (sink->dests.empty())
            std::this_thread::sleep_for(std::chrono::seconds(1));

        /* 重置超时时间 */
        timerclear(&timer);
        timer.tv_sec = 1;
        timer.tv_usec = 0;

        /* 检查套接字可读性 */
        FD_ZERO(&set);
        FD_SET(skt, &set);
        if (select(0, &set, nullptr, nullptr, &timer) <= 0) continue;
        if (!FD_ISSET(skt, &set)) continue;

        /* 接收用户数据报协议数据包 */
        pckl = recvfrom(skt, pck, sizeof pck, 0, reinterpret_cast<SOCKADDR *>(&saddr), &saddrl);
        if (SOCKET_ERROR == pckl) {
            *env << "H264VideoUDPSoutce: Error, recvfrom() failed with code " << WSAGetLastError() << ".\n";
            continue;
        }

        /* 将接收到的数据，组装成 H.264 网络抽象层单元 */
        // 若上一单元已组装完毕，则将其压入目的地缓冲池，并重置 NALUB
        if (0 < nalubl && (
            0 == pck[0] && 0 == pck[1] && 1 == pck[2] ||
            0 == pck[0] && 0 == pck[1] && 0 == pck[2] && 1 == pck[3]
            )) {
            sink->dests.mtx.lock();
            for (auto dest : sink->dests.set) {
                H264VideoUDPSource::Buf *destbuf;
                while (nullptr == (destbuf = dest->bufs.allocateforce()))
                    std::this_thread::sleep_for(std::chrono::microseconds(100));
                if (0 != (discarded = destbuf->cpyf(nalub, nalubl)))
                    *env << "H264VideoUDPSource: A NALU size is too large for SrcBuf, "
                    << discarded << " bytes data has been discarded.\n";
                dest->bufs.push(destbuf);
            }
            sink->dests.mtx.unlock();
            memset(nalub, 0, sizeof nalub);
            nalubl = 0;
            nalufc = 0;
        } else
            if (NALUBS / PCKS / 0.01 - 1 < ++nalufc && 0 == nalufc % (NALUBS / PCKS))
                *env << "H264VideoUDPSource: " << nalufc << " consecutive packets without NALU start_codes,"
                << " port " << ntohs(raddr.sin_port) << " is receiving H.264 elementary stream?"
                << " The sender " << saddr.sin_addr.s_net << "." << saddr.sin_addr.s_host << "." << saddr.sin_addr.s_lh << "." << saddr.sin_addr.s_impno << ":" << ntohs(saddr.sin_port) << ".\n";
        // 将接收到的数据追加至 NALUB
        actual = pckl < NALUBS - nalubl ? pckl : NALUBS - nalubl;
        memcpy_s(nalub + nalubl, NALUBS - nalubl, pck, actual);
        nalubl += actual;
        if (0 < pckl - actual)
            *env << "H264VideoUDPSource: A NALU size is too large for NALUB, "
            << pckl - actual << " bytes data has been discarded.\n";
    }

    /* 关闭套接字 */ {
        *env << "H264VideoUDPServer: Close socket...";
        closesocket(skt);
        *env << "done.\n";
    }

    /* Windows Socket 的启用和关闭由 LIVE555 管理 */

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
    auto sink = gSinks.find(ntohs(skt->port().num()));
    assert(sink);
    sink->dests.insert(this);
}

H264VideoUDPSource::~H264VideoUDPSource()
{
    auto sink = gSinks.find(ntohs(skt->port().num()));
    assert(sink);
    sink->dests.erase(this);
}

void H264VideoUDPSource::doGetNextFrame()
{
    /* 若当前处理缓存为空，则在缓存池中取缓存 */
    if (nullptr == curb)
        while (nullptr == (curb = bufs.pop()))
            std::this_thread::sleep_for(std::chrono::microseconds(100));

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
    gSinks.apply(env, port);
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
