/** \copyright The MIT License */
#include "H264VideoUDPSource.hpp"

#include <thread>

namespace rrdemo {
namespace cdom {
namespace live555 {

void H264VideoUDPSource::newpck(const PACKET &pck, const SOCKADDR_IN &, const SOCKADDR_IN &)
{
    /* 判断包是否含有 NAL 单元头 */
    bool isheader;
    do {
        if (pck.len < 4) {
            isheader = false; break;
        }

        if (!(
            0 == pck.data[0] && 0 == pck.data[1] && 1 == pck.data[2] ||
            0 == pck.data[0] && 0 == pck.data[1] && 0 == pck.data[2] && 1 == pck.data[3])) {
            isheader = false; break;
        }

        isheader = true;

    } while (false);

    /* 若上一单元已组装完毕，则将其压入缓存池，并重置 NAL 单元缓存 */
    if (isheader && 0 < nalub.len) {
        Buf *buf;
        while (nullptr == (buf = bufs.allocateforce()))
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        const auto discarded = buf->cpyf(nalub.data, nalub.len);
        if (0 < discarded)
            envir() << "H264VideoUDPSource: A NALU size is too large for SrcBuf, "
            << discarded << " bytes data has been discarded.\n";
        bufs.push(buf);
        nalub.len = 0;
        nalub.pcknum = 0;
    } else
        if (ceil(nalub.SIZE / pck.SIZE) / 0.01 - 1 < ++nalub.pcknum &&
            0 == nalub.pcknum % static_cast<int>(ceil(nalub.SIZE / pck.SIZE)))
            envir() << "H264VideoUDPSource: " << nalub.pcknum << " consecutive packets without NALU start_codes,"
            << " the port is receiving H.264 elementary stream?";

    /* 将包数据追加至 NAL 单元缓存 */
    const auto free = nalub.SIZE - nalub.len;
    const auto actual = pck.len < free ? pck.len : free;  // min
    memcpy_s(nalub.data + nalub.len, free, pck.data, actual);
    nalub.len += actual;
    const auto discarded = pck.len - actual;
    if (0 < discarded)
        envir() << "H264VideoUDPSource: A NALU size is too large for NALUB, "
        << discarded << " bytes data has been discarded.\n";
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
