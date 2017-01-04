/** \copyright The MIT License */
#include "FLVDemuxADTSAudioUDPSourceHelper.hpp"

#include "FLVDemux.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

std::map<u_int16_t, FLVDemuxADTSAudioUDPSourceHelper *> FLVDemuxADTSAudioUDPSourceHelper::map;
std::mutex FLVDemuxADTSAudioUDPSourceHelper::mtx;

bool FLVDemuxADTSAudioUDPSourceHelper::allo(UsageEnvironment * const env, const u_int16_t port)
{
    if (map.end() != map.find(port)) return false;
    mtx.lock(); {
        map.insert(std::pair<u_int16_t, FLVDemuxADTSAudioUDPSourceHelper *>(
            port, createNew(*env, port)));
    } mtx.unlock();
    return true;
}

FLVDemuxADTSAudioUDPSourceHelper *FLVDemuxADTSAudioUDPSourceHelper::find(const u_int16_t port)
{
    if (map.end() == map.find(port)) return nullptr;
    return map[port];
}

void FLVDemuxADTSAudioUDPSourceHelper::newpck(const PACKET &pck, const SOCKADDR_IN &, const SOCKADDR_IN &)
{
    if (pck.len < sizeof(FLVDemux::FLVH) || pck.len < sizeof(FLVDemux::FLVBTH))
        return;

    FLVDemux::FLVH flvh;        //< FLV 文件头（FLV Header）。
    size_t flvhcur;             //< FLVH 的固定“游”标。
    FLVDemux::FLVBTH flvbth;    //< FLV 文件体 Tag 头（FLV Body Tag Header）。
    size_t flvbthcur;           //< FLVBTH 的固定“游”标。
    FLVDemux::FLVBTD flvbtd;    //< FLV 文件体 Tag 数据（FLV Body Tag Data）。
    size_t flvbtdcur;           //< FLVBTD 的固定“游”标。
    FLVDemux::FLVBPTS flvbpts;  //< FLV 文件体 上一 Tag 尺寸（FLV Body Previous Tag Size）。
    // size_t flvbptscur;       //< FLVBPTS 的固定“游”标。
    size_t cur {0};             //< 游标（Cursor）。

    while (true) {
        if (0x46u == pck.data[0] && 0x4Cu == pck.data[1] && 0x56u == pck.data[2]) {
            /* FLV HEADER */

            // FLV HEADER
            flvhcur = cur;
            // Signature
            cur += 3;
            // Version
            cur += 1;
            // TypeFlagsReserved
            cur += 0;
            // TypeFlagsAudio
            cur += 0;
            // TypeFlagsReserved2
            cur += 0;
            // TypeFlagsVideo
            cur += 1;
            // DataOffset
            flvh.DataOffset =
                static_cast<uint32_t>(pck.data[cur]) << 24 |
                static_cast<uint32_t>(pck.data[cur + 1]) << 16 |
                static_cast<uint32_t>(pck.data[cur + 2]) << 8 |
                static_cast<uint32_t>(pck.data[cur + 3]);
            cur = flvhcur + flvh.DataOffset;

            // FLV BODY PREVIOUS TAG SIZE
            // flvbptscur = cur;
            // PreviousTagSize
            flvbpts.PreviousTagSize =
                static_cast<uint32_t>(pck.data[cur]) << 24 |
                static_cast<uint32_t>(pck.data[cur + 1]) << 16 |
                static_cast<uint32_t>(pck.data[cur + 2]) << 8 |
                static_cast<uint32_t>(pck.data[cur + 3]);
            cur += 4;

            assert(0 == flvbpts.PreviousTagSize);

        } else if (0x08u == pck.data[0] || 0x09u == pck.data[0] || 0x12u == pck.data[0]) {
            /* FLV BODY TAG */

            // FLV BODY TAG HEADER
            flvbthcur = cur;
            // TagType
            flvbth.TagType = pck.data[cur];
            cur += 1;
            // DataSize
            flvbth.DataSize =
                static_cast<uint32_t>(pck.data[cur]) << 16 |
                static_cast<uint32_t>(pck.data[cur + 1]) << 8 |
                static_cast<uint32_t>(pck.data[cur + 2]);
            cur += 3;
            // Timestamp
            cur += 3;
            // TimestampExtended
            cur += 1;
            // StreamID
            cur += 3;

            // FLV BODY TAG DATA
            flvbtdcur = cur;
            if (0x09u == flvbth.TagType) {
                // SoundFormat
                flvbtd.AudioType.SoundFormat = (pck.data[cur] & 0xF0u) >> 4;
                cur += 0;
                // SoundRate
                cur += 0;
                // SoundSize
                cur += 0;
                // SoundType
                cur += 1;
                if (0x0Au == flvbtd.AudioType.SoundFormat) {
                    // AACPacketType
                    cur += 1;
                }
                // Data
                // TODO!
                cur += flvbth.DataSize - (cur - flvbtdcur);

            } else {
                // Skip
                cur += flvbth.DataSize;

            }

            // FLV BODY PREVIOUS TAG SIZE
            // flvbptscur = cur;
            // PreviousTagSize
            flvbpts.PreviousTagSize =
                static_cast<uint32_t>(pck.data[cur]) << 24 |
                static_cast<uint32_t>(pck.data[cur + 1]) << 16 |
                static_cast<uint32_t>(pck.data[cur + 2]) << 8 |
                static_cast<uint32_t>(pck.data[cur + 3]);
            cur += 4;

            assert(cur - flvbthcur == flvbpts.PreviousTagSize);

        } else {
            /* UNKNOWN FORMAT */

            envir() << "FLVDemuxADTSAudioUDPSourceHelper: Bad header, not FLV header nor FLV body tag header.\n";
            return;

        }

        assert(cur + 1 <= pck.len);
        if (cur + 1 < pck.len) continue;
        else                   break;
    }
}


}// namespace live555
}// namespace cdom
}// namespace rrdemo
