/** \copyright The MIT License */
#include "FLVDemuxH264VideoUDPSource.hpp"

#include <thread>

namespace rrdemo {
namespace cdom {
namespace live555 {

void FLVDemuxH264VideoUDPSource::newpck(const PACKET &pck, const SOCKADDR_IN &, const SOCKADDR_IN &)
{
    /* 判断包是否含有 NAL 单元头 */
    bool isheader;
    do {
        if (pck.len < sizeof(NALUH)) {
            isheader = false; break;
        }

        if (0x00 == pck.data[0] && 0x00 == pck.data[1] && 0x00 == pck.data[2] && 0x01 == pck.data[3]) {
            // 起始码 4 字节变种。
        } else if (0x00 == pck.data[0] && 0x00 ==pck.data[1] && 0x01 == pck.data[2]) {
            // 起始码 3 字节变种。
        } else {
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
            envir() << "FLVDemuxH264VideoUDPSource: A NALU size is too large for SrcBuf, "
            << discarded << " bytes data has been discarded.\n";
        bufs.push(buf);
        nalub.len = 0;
        nalub.pcknum = 0;
    } else
        if (ceil(nalub.SIZE / pck.SIZE) / 0.01 - 1 < ++nalub.pcknum &&
            0 == nalub.pcknum % static_cast<int>(ceil(nalub.SIZE / pck.SIZE)))
            envir() << "FLVDemuxH264VideoUDPSource: " << nalub.pcknum << " consecutive packets without NALU start_codes,"
            << " the port is receiving H.264 elementary stream?";

    /* 将包数据追加至 NAL 单元缓存 */
    const auto free = nalub.SIZE - nalub.len;
    const auto actual = pck.len < free ? pck.len : free;  // min
    memcpy_s(nalub.data + nalub.len, free, pck.data, actual);
    nalub.len += actual;
    const auto discarded = pck.len - actual;
    if (0 < discarded)
        envir() << "FLVDemuxH264VideoUDPSource: A NALU size is too large for NALUB, "
        << discarded << " bytes data has been discarded.\n";
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
