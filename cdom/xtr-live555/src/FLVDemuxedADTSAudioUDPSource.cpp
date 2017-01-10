/** \copyright The MIT License */
#include "FLVDemuxedADTSAudioUDPSource.hpp"

#include "formats/FlashVideo.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

void FLVDemuxedADTSAudioUDPSource::
whenNewIPv4UDPPacketReceived(const IPv4UDPPacketData & pkt, const SOCKADDR_IN &, const SOCKADDR_IN &)
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
            envir() << "FLVDemuxedADTSAudioUDPSource: " << flvBuffer.packetCount
            << " consecutive packets without FLV tag header, the port is receiving FLV stream?";

    const size_t actlen = fmin(pkt.length, flvBuffer.SIZE - flvBuffer.length);  // actual length
    memcpy_s(flvBuffer.data + flvBuffer.length, actlen, pkt.data, actlen);
    flvBuffer.length += actlen;
    flvBuffer.previousPacketDataSize = pkt.length;
    const auto dsclen = pkt.length - actlen;
    if (0 < dsclen)
        envir() << "FLVDemuxedADTSAudioUDPSource: A FLV tag size is too large for FLV buffer, "
        << dsclen << " bytes data has been discarded.\n";
}

void FLVDemuxedADTSAudioUDPSource::
whenNewFLVBufferReady(FlashVideoBuffer &flvBuf)
{
    const auto &TAG_HEADER_SIZE = FLVTagHeader::TAG_HEADER_SIZE;
    const auto &PREVIOUS_TAG_SIZE_SIZE = FLVPreviousTagSize::PREVIOUS_TAG_SIZE_SIZE;

    FLVTagHeader tagHeader;
    if (!tagHeader.parse(flvBuf.data, flvBuf.length)) {
        envir() << "FLVDemuxedADTSAudioUDPSource: Bad tag header.\n";
        return;
    }
    if (!tagHeader.isAudio())
        return;
    const auto tagSize = TAG_HEADER_SIZE + tagHeader.getDataSize();
    if (flvBuf.length != tagSize + PREVIOUS_TAG_SIZE_SIZE) {
        envir() << "FLVDemuxedADTSAudioUDPSource: Bad DataSize.\n";
        return;
    }

    size_t cur {};  // cursor
    FLVTagDataAudio tagData;
    if (!tagData.parse(flvBuf.data + TAG_HEADER_SIZE, flvBuf.length - TAG_HEADER_SIZE)) {
        envir() << "FLVDemuxedADTSAudioUDPSource: Bad tag data.\n";
        return;
    }
    if (!tagData.isAAC()) {
        envir() << "FLVDemuxedH264VideoUDPSource: Bad SoundFormat.\n";
        return;
    }

    whenNewADTSFBufferReady(adtsfBuffer);

    FLVPreviousTagSize preTagSize;
    if (!preTagSize.parse(flvBuf.data + tagSize, flvBuf.length - tagSize)) {
        envir() << "FLVDemuxedADTSAudioUDPSource: Bad previous tag size.\n";
        return;
    }
    if (tagSize != preTagSize.getSize())
        envir() << "FLVDemuxedADTSAudioUDPSource: Bad PreviousTagSize.\n";
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
