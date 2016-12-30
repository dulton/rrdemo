/** \copyright The MIT License */
#include "H264VideoUDPSource.hpp"

#include <thread>

namespace rrdemo {
namespace cdom {
namespace live555 {

void H264VideoUDPSource::newpck(const size_t PCKS, const uint8_t* const pck, const size_t pckl)
{
    // 若上一单元已组装完毕，则将其压入缓冲池，并重置 NALUB
    if (0 < nalubl && (
        0 == pck[0] && 0 == pck[1] && 1 == pck[2] ||
        0 == pck[0] && 0 == pck[1] && 0 == pck[2] && 1 == pck[3]
        )) {
        Buf *buf;
        while (nullptr == (buf = bufs.allocateforce()))
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        size_t discarded;
        if (0 != (discarded = buf->cpyf(nalub, nalubl)))
            envir() << "H264VideoUDPSource: A NALU size is too large for SrcBuf, "
            << discarded << " bytes data has been discarded.\n";
        bufs.push(buf);
        nalubl = 0;
        nalufc = 0;
    } else
        if (ceil(NALUBS / PCKS) / 0.01 - 1 < ++nalufc && 0 == nalufc % static_cast<int>(ceil(NALUBS / PCKS)))
            envir() << "H264VideoUDPSource: " << nalufc << " consecutive packets without NALU start_codes,"
            << " the port is receiving H.264 elementary stream?";

    // 将接收到的数据追加至 NALUB
    size_t actual {pckl < NALUBS - nalubl ? pckl : NALUBS - nalubl};  // min
    memcpy_s(nalub + nalubl, NALUBS - nalubl, pck, actual);
    nalubl += actual;
    if (0 < pckl - actual)
        envir() << "H264VideoUDPSource: A NALU size is too large for NALUB, "
        << pckl - actual << " bytes data has been discarded.\n";
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
