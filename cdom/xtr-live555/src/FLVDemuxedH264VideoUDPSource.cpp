/** \copyright The MIT License */
#include "FLVDemuxedH264VideoUDPSource.hpp"

#include "formats/FlashVideo.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

void FLVDemuxedH264VideoUDPSource::
whenNewIPv4UDPPacketReceived(const IPv4UDPPacketData &pkt, const SOCKADDR_IN &, const SOCKADDR_IN &)
{
    auto isReadyHalf = false;
    if (!FLVTagHeader::IsTagHeader(pkt.data, pkt.length))
        /*skip*/;
    else if (1472 == flvBuffer.previousPacketDataSize)  // 上一包为“满包”，不似 FLV 尾
        /*skip*/;
    else
        isReadyHalf = true;

    if (isReadyHalf && 0 < flvBuffer.length) {
        whenNewFLVBufferReady(flvBuffer);
        flvBuffer.length = 0;
        flvBuffer.packetCount = 0;
    } else
        if (500 <= ++flvBuffer.packetCount)
            envir() << "FLVDemuxedH264VideoUDPSource: " << flvBuffer.packetCount
            << " consecutive packets without FLV tag header, the port is receiving FLV stream?";

    const size_t actlen = fmin(pkt.length, flvBuffer.SIZE - flvBuffer.length);  // actual length
    memcpy_s(flvBuffer.data + flvBuffer.length, actlen, pkt.data, actlen);
    flvBuffer.length += actlen;
    flvBuffer.previousPacketDataSize = pkt.length;
    const auto dsclen = pkt.length - actlen;
    if (0 < dsclen)
        envir() << "FLVDemuxedH264VideoUDPSource: A FLV tag size is too large for FLV buffer, "
        << dsclen << " bytes data has been discarded.\n";
}

void FLVDemuxedH264VideoUDPSource::
whenNewFLVBufferReady(FlashVideoBuffer &flvBuf)
{
    const auto &TAG_HEADER_SIZE = FLVTagHeader::TAG_HEADER_SIZE;
    const auto &PREVIOUS_TAG_SIZE_SIZE = FLVPreviousTagSize::PREVIOUS_TAG_SIZE_SIZE;

    FLVTagHeader tagHeader;
    if (!tagHeader.parse(flvBuf.data, flvBuf.length)) {
        envir() << "FLVDemuxedH264VideoUDPSource: Bad tag header.\n";
        return;
    }
    if (!tagHeader.isVideo())
        return;
    const auto tagSize = TAG_HEADER_SIZE + tagHeader.getDataSize();
    if (flvBuf.length != tagSize + PREVIOUS_TAG_SIZE_SIZE) {
        envir() << "FLVDemuxedH264VideoUDPSource: Bad DataSize.\n";
        return;
    }

    size_t cur {};  // cursor
    FLVTagDataVideo tagData;
    if (!tagData.parse(flvBuf.data + TAG_HEADER_SIZE, flvBuf.length - TAG_HEADER_SIZE)) {
        envir() << "FLVDemuxedH264VideoUDPSource: Bad tag data.\n";
        return;
    }
    if (!tagData.isAVC()) {
        envir() << "FLVDemuxedH264VideoUDPSource: Bad CodecID.\n";
        return;
    }

    whenNewNALUBufferReady(naluBuffer);

    FLVPreviousTagSize preTagSize;
    if (!preTagSize.parse(flvBuf.data + tagSize, flvBuf.length - tagSize)) {
        envir() << "FLVDemuxedH264VideoUDPSource: Bad previous tag size.\n";
        return;
    }
    if (tagSize != preTagSize.PreviousTagSize)
        envir() << "FLVDemuxedH264VideoUDPSource: Bad PreviousTagSize.\n";
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
