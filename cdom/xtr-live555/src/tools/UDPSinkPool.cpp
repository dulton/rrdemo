/** \copyright The MIT License */
#include "UDPSinkPool.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

IPv4UDPSinkPool::
~IPv4UDPSinkPool()
{
    mapMutex.lock(); {
        for (auto &sink : map)
            free(sink.first);
    } mapMutex.unlock();
}

IPv4UDPSink *IPv4UDPSinkPool::
allocate(const uint16_t port)
{
    if (map.end() == map.find(port)) {
        auto sink = new IPv4UDPSink(port);
        mapMutex.lock(); {
            map.insert(std::make_pair(port, sink));
        } mapMutex.unlock();
    }
    return map[port];
}

bool IPv4UDPSinkPool::
free(const uint16_t port)
{
    if (map.end() == map.find(port))
        return true;
    if (!map[port]->processorSet.empty())
        return false;
    auto sink = map[port];
    mapMutex.lock(); {
        map.erase(port);
    } mapMutex.unlock();
    delete sink;
    return true;
}

IPv4UDPSink *IPv4UDPSinkPool::
find(const uint16_t port)
{
    if (map.end() == map.find(port))
        return nullptr;
    return map[port];
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
