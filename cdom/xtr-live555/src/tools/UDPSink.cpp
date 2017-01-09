/** \copyright The MIT License */
#include "UDPSink.hpp"

namespace {

using rrdemo::cdom::live555::IPv4UDPSink;
using rrdemo::cdom::live555::IPv4UDPPacketData;

void IPv4UDPSinkReceiverThreadFunction(IPv4UDPSink * const sink)
{
    SOCKET skt;  // socket
    skt = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (INVALID_SOCKET == skt) {
        WSAGetLastError();
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    SOCKADDR_IN rcvaddr {};  //< receiver address
    rcvaddr.sin_family = AF_INET;
    rcvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    rcvaddr.sin_port = htons(sink->port);
    if (SOCKET_ERROR == bind(skt, reinterpret_cast<PSOCKADDR>(&rcvaddr), sizeof rcvaddr)) {
        WSAGetLastError();
        closesocket(skt);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    int so_rcvbuf {1 << 24};
    if (SOCKET_ERROR == setsockopt(skt, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<const char *>(&so_rcvbuf), sizeof so_rcvbuf)) {
        WSAGetLastError();
        exit(EXIT_FAILURE);
    }

    TIMEVAL timer {};
    FD_SET set {};
    SOCKADDR_IN sndaddr {};  //< sender address
    int sndaddrlen {sizeof sndaddr};  //< sender address length
    IPv4UDPPacketData pkt;  // packet data

    while (sink->receiverThreadLoopFlag) {
        while (sink->processorSet.empty())
            std::this_thread::sleep_for(std::chrono::seconds(1));

        timerclear(&timer);
        timer.tv_sec = 1;
        timer.tv_usec = 0;

        FD_ZERO(&set);
        FD_SET(skt, &set);
        if (select(0, &set, nullptr, nullptr, &timer) <= 0)
            continue;
        if (!FD_ISSET(skt, &set))
            continue;

        pkt.length = recvfrom(skt, reinterpret_cast<char *>(pkt.data), pkt.SIZE, 0, reinterpret_cast<SOCKADDR *>(&sndaddr), &sndaddrlen);
        if (SOCKET_ERROR == pkt.length) {
            WSAGetLastError();
            continue;
        }

        sink->processorSetMutex.lock(); {
            for (auto dest : sink->processorSet)
                dest->whenNewIPv4UDPPacketReceived(pkt, rcvaddr, sndaddr);
        } sink->processorSetMutex.unlock();
    }

    closesocket(skt);
}

}// namespace

namespace rrdemo {
namespace cdom {
namespace live555 {

IPv4UDPSink::
IPv4UDPSink(const uint16_t port) :
port {port}
{
    receiverThreadLoopFlag = true;
    receiverThread = new std::thread(IPv4UDPSinkReceiverThreadFunction, this);
}

IPv4UDPSink::
~IPv4UDPSink()
{
    receiverThreadLoopFlag = false;
    receiverThread->join();
}

void IPv4UDPSink::
insertProcessor(IPv4UDPProcessor * const processor)
{
    processorSetMutex.lock(); {
        processorSet.insert(processor);
    } processorSetMutex.unlock();
}

void IPv4UDPSink::
eraseProcessor(IPv4UDPProcessor * const processor)
{
    processorSetMutex.lock(); {
        processorSet.erase(processor);
    } processorSetMutex.unlock();
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
