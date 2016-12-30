/** \copyright The MIT License */
#include "BasicUDPSource.hpp"

#include <map>
#include <set>
#include <thread>

#include <live555/Groupsock.hh>

//#pragma comment(lib, "Ws2_32.lib")

namespace {

using rrdemo::cdom::live555::BasicUDPSource;

/// 接收者类型。
struct sink_t {
    u_int16_t port;    //< 收流端口。
    std::thread *thr;  //< 收流线程。
    bool thrloop;      //< 收流循环标志。
    /// 目的地集类型。
    struct dests_t {
        std::set<BasicUDPSource *> set;  //< 目的地集实体。
        std::mutex mtx;                      //< 目的地集锁。
        /// 判断目的地集是否为空。
        bool empty() const { return set.empty(); }
        /// 插入目的地。
        void insert(BasicUDPSource * const dest);
        /// 擦除目的地。
        void erase(BasicUDPSource * const dest);
    } dests;           //< 目的地集。
};

void sink_t::dests_t::insert(BasicUDPSource * const dest)
{
    mtx.lock(); {
        set.insert(dest);
    } mtx.unlock();
}

void sink_t::dests_t::erase(BasicUDPSource * const dest)
{
    mtx.lock(); {
        set.erase(dest);
    } mtx.unlock();
}

/// 接收者集类。
class Sinks {
public:
    /// 分配接收者.
    bool allo(UsageEnvironment * const env, const u_int16_t port);
    /// 释放接收者。
    bool free(const u_int16_t port);
    /// 寻找接收者。
    sink_t *find(const u_int16_t port);
private:
    std::map<u_int16_t, sink_t *> map;  //< 接收者集实体。
    std::mutex mtx;                     //< 接收者集锁。
} gSinks;  //< 接收者集。

void sink_thr_func(UsageEnvironment * const env, sink_t * sink);
bool Sinks::allo(UsageEnvironment * const env, const u_int16_t port)
{
    if (map.end() != map.find(port)) return false;
    auto sink = new sink_t;
    sink->port = port;
    sink->thrloop = true;
    sink->thr = new std::thread(sink_thr_func, env, sink);
    mtx.lock(); {
        map.insert(std::pair<u_int16_t, sink_t *>(port, sink));
    } mtx.unlock();
    return true;
}

bool Sinks::free(const u_int16_t port)
{
    if (map.end() == map.find(port)) return false;
    if (!map[port]->dests.empty()) return false;
    auto sink = map[port];
    mtx.lock(); {
        map.erase(port);
    } mtx.unlock();
    sink->thrloop = false;
    sink->thr->join();
    delete sink->thr;
    delete sink;
    return true;
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
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    /* Windows Socket 的启用和关闭由 LIVE555 管理 */

    SOCKET skt;  //< SocKeT。
    /* 创建套接字 */ {
        *env << "BasicUDPSource: Creating socket...";
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
        *env << "BasicUDPSource: Binding address...";
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
    uint8_t pck[PCKS] {};              //< udp PaCKet。
    size_t pckl;                       //< udp PaCKet Length。

    /* 收流与处理 */
    while (sink->thrloop) {
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
        pckl = recvfrom(skt, reinterpret_cast<char *>(pck), sizeof pck, 0,
                        reinterpret_cast<SOCKADDR *>(&saddr), &saddrl);
        if (SOCKET_ERROR == pckl) {
            *env << "BasicUDPSource: Error, recvfrom() failed with code " << WSAGetLastError() << ".\n";
            continue;
        }

        /* 将接收到的数据交予各目的地回调处理函数处理 */
        sink->dests.mtx.lock(); {
            for (auto dest : sink->dests.set)
                dest->newpck(PCKS, pck, pckl);
        } sink->dests.mtx.unlock();
    }

    /* 关闭套接字 */ {
        *env << "BasicUDPSource: Close socket...";
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

BasicUDPSource::BasicUDPSource(
    UsageEnvironment &env, Groupsock *skt) :
    FramedSource(env), skt {skt}
{
    auto sink = gSinks.find(ntohs(skt->port().num()));
    assert(sink);
    sink->dests.insert(this);
}

BasicUDPSource::~BasicUDPSource()
{
    auto sink = gSinks.find(ntohs(skt->port().num()));
    assert(sink);
    sink->dests.erase(this);
}

void BasicUDPSource::doGetNextFrame()
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
        0, reinterpret_cast<TaskFunc *>(afterGetting), this);
}

void BasicUDPSource::initializeSourceBeforeEventLoop(UsageEnvironment *env, u_int16_t port)
{
    if (!gSinks.allo(env, port))
        assert(false);
}

void BasicUDPSource::newpck(const size_t PCKS, const uint8_t* const pck, const size_t pckl)
{
    Buf *buf;
    while (nullptr == (buf = bufs.allocateforce()))
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    size_t discarded;
    if (0 != (discarded = buf->cpyf(pck, pckl)))
        envir() << "BasicUDPSource: A UDP pack size is too large for SrcBuf, "
        << discarded << " bytes data has been discarded.\n";
    bufs.push(buf);
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
