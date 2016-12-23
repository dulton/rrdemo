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
        /* 线程循环前初始化 */
        struct timeval timeout {};

        SOCKET skt {socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)};
        int sorcvbuf {1 << 24};
        setsockopt(skt, SOL_SOCKET, SO_RCVBUF,
                   reinterpret_cast<const char *>(&sorcvbuf), sizeof sorcvbuf);

        SOCKADDR_IN addr {};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = obj->port.num();

        fd_set set;

        if (bind(skt, reinterpret_cast<SOCKADDR *>(&addr), sizeof addr))
            exit(WSAGetLastError());

        uint8_t recv[300000] {};
        /* 线程循环 */
        while (obj->sinkloop) {
            memset(&timeout, 0, sizeof timeout);
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;

            FD_ZERO(&set);
            FD_SET(skt, &set);

            if (select(skt + 1, &set, nullptr, nullptr, &timeout) <= 0)
                continue;

            if (FD_ISSET(skt, &set)) {
                int addrlen {sizeof addr};
                int recvlen {recvfrom(
                    skt, reinterpret_cast<char *>(recv), sizeof recv,
                    0, reinterpret_cast<SOCKADDR *>(&addr), &addrlen)};
                if (recvlen <= 0)
                    continue;

                obj->quemtx.lock();
                {
                    if (!obj->idleque.empty()) {
                        auto &buf = obj->idleque.front();
                        obj->idleque.pop();

                        memcpy_s(buf.data, 300000, recv, recvlen);
                        buf.size = recvlen;

                        obj->dataque.push(buf);

                    } else {
                        auto &buf = obj->dataque.front();
                        obj->dataque.pop();

                        memcpy_s(buf.data, 300000, recv, recvlen);
                        buf.size = recvlen;

                        obj->dataque.push(buf);

                    }

                }
                obj->quemtx.unlock();
            }
        }

        closesocket(skt);

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
