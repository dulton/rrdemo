/** \file
 *  \author zhengrr
 *  \date 2016-12-30 – 2017-1-9
 *  \copyright The MIT License
 */
#ifndef RRDEMO__CDOM__LIVE555__USER_DATAGRAM_PROTOCOL_PACKET__HPP
#define RRDEMO__CDOM__LIVE555__USER_DATAGRAM_PROTOCOL_PACKET__HPP

#include <cstdint>

namespace rrdemo {
namespace cdom {
namespace live555 {

/// 网际协议四版－用户数据报协议－包－负载数据。
struct IPv4UDPPacketData final {
    static const size_t SIZE {65507};
    uint8_t data[SIZE] {};
    size_t length;
};

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif //RRDEMO__CDOM__LIVE555__USER_DATAGRAM_PROTOCOL_PACKET__HPP
