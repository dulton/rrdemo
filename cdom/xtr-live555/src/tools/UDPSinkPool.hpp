/** \file
 *  \author zhengrr
 *  \date 2016-12-30 – 2017-1-9
 *  \copyright The MIT License
 */
#ifndef RRDEMO__CDOM__LIVE555__UDP_SINK_POOL__HPP
#define RRDEMO__CDOM__LIVE555__UDP_SINK_POOL__HPP

#include <map>
#include <mutex>

#include "UDPSink.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

/// 用户数据报协议接收器池。
class IPv4UDPSinkPool final {
    explicit IPv4UDPSinkPool(const IPv4UDPSinkPool &) = delete;
    explicit IPv4UDPSinkPool(IPv4UDPSinkPool &&) = delete;
    IPv4UDPSinkPool &operator=(const IPv4UDPSinkPool &) = delete;
    IPv4UDPSinkPool &operator=(IPv4UDPSinkPool &&) = delete;

public:
    /// 构造函数。
    explicit IPv4UDPSinkPool() = default;

    /// 析构函数。
    ~IPv4UDPSinkPool();

    /// 分配接收器。
    IPv4UDPSink *allocate(const uint16_t port);

    /// 释放接收器。
    bool free(const uint16_t port);

    /// 查找接收器。
    IPv4UDPSink *find(const uint16_t port);

private:
    std::map<uint16_t, IPv4UDPSink *> map;  //< 接收者集。
    std::mutex mapMutex;                    //< 接收者集锁。

};// class UDPSinkPool

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// RRDEMO__CDOM__LIVE555__UDP_SINK_POOL__HPP
