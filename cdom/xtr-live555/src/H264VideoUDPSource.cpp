/** \copyright The MIT License */
#include "H264VideoUDPSource.hpp"

#include <thread>

#include "tools/H264NetworkAbstractLayerUnit.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

void H264VideoUDPSource::whenNewIPv4UDPPacketReceived(
    const IPv4UDPPacketData &pck, const SOCKADDR_IN &, const SOCKADDR_IN &)
{
    using NALU = H264NetworkAbstractLayerUnit;
    auto &nalu = h264NALUBuffer;

    if (pck.length < sizeof(H264NALUHeader))
        return;

    if (NALU::IsHeader(pck.data, pck.length) && 0 < nalu.length) {
        BytesBuffer *buf;
        while (nullptr == (buf = frameBufferPool.allocateForce()))
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        const auto discarded = buf->copyDataFrom(nalu.data, nalu.length);
        if (0 < discarded)
            envir() << "H264VideoUDPSource: A NALU size is too large for SrcBuf, " << discarded << " bytes data has been discarded.\n";
        frameBufferPool.push(buf);
        nalu.length = 0;
        nalu.packetCount = 0;
    } else
        if (500 <= nalu.packetCount)
            envir() << "H264VideoUDPSource: " << nalu.packetCount << " consecutive packets without NALU start_codes, the port is receiving H.264 elementary stream?";

    const size_t actlen = fmin(pck.length, nalu.SIZE - nalu.length);  // actual length
    memcpy_s(nalu.data + nalu.length, actlen, pck.data, actlen);
    nalu.length += actlen;
    const auto discarded = pck.length - actlen;
    if (0 < discarded)
        envir() << "H264VideoUDPSource: A NALU size is too large for NALUB, "
        << discarded << " bytes data has been discarded.\n";
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
