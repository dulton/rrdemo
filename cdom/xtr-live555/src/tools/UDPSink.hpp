/** \file
 *  \author zhengrr
 *  \date 2016-12-30 – 2017-1-9
 *  \copyright The MIT License
 */
#ifndef RRDEMO__CDOM__LIVE555__UDP_SINK__HPP
#define RRDEMO__CDOM__LIVE555__UDP_SINK__HPP

#include <mutex>
#include <set>
#include <thread>

#include "UDPProcessor.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

/// 网际协议四版用户数据报协议接收器。
class IPv4UDPSink final {
    explicit IPv4UDPSink() = delete;
    explicit IPv4UDPSink(const IPv4UDPSink &) = delete;
    explicit IPv4UDPSink(IPv4UDPSink &&) = delete;
    IPv4UDPSink &operator=(const IPv4UDPSink &) = delete;
    IPv4UDPSink &operator=(IPv4UDPSink &&) = delete;

public:
    /// 构造函数。
    explicit IPv4UDPSink(const uint16_t port);

    /// 析构函数。
    ~IPv4UDPSink();

    void insertProcessor(IPv4UDPProcessor * const processor);

    void eraseProcessor(IPv4UDPProcessor * const processor);

    uint16_t port;                              //< 端口；
    std::thread *receiverThread {};             //< 收流线程；
    bool receiverThreadLoopFlag;                //< 收流线程循环标志位。
    std::set<IPv4UDPProcessor *> processorSet;  //< 处理器集；
    std::mutex processorSetMutex;               //< 处理器集锁。

};// class IPv4UDPSink

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// RRDEMO__CDOM__LIVE555__UDP_SINK__HPP
