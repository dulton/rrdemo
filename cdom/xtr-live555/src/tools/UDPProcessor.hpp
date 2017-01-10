/** \file
 *  \author zhengrr
 *  \date 2016-12-30 – 2017-1-9
 *  \copyright The MIT License
 */
#ifndef RRDEMO__CDOM__LIVE555__UDP_PROCESSOR_INTERFACE__HPP
#define RRDEMO__CDOM__LIVE555__UDP_PROCESSOR_INTERFACE__HPP

#include <WinSock2.h>

#include "formats/UserDatagramProtocolPacket.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

/// 网际协议四版用户数据报协议处理器接口。
struct IPv4UDPProcessor {
    virtual ~IPv4UDPProcessor()
    {}

    /// 当新的网际协议四版－用户数据报协议－包被接收时（的回调函数）。
    /** \param packetData 包数据。
     *  \param receiverAddress 接收者地址。
     *  \param senderAddress 发送者地址。
     */
    virtual void whenNewIPv4UDPPacketReceived(
        const IPv4UDPPacketData &packetData,
        const SOCKADDR_IN &receiverAddress,
        const SOCKADDR_IN &senderAddress)
    {}
};

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// RRDEMO__CDOM__LIVE555__UDP_PROCESSOR_INTERFACE__HPP
