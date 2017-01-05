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
    FLVDemux::FLVBTH flvbth;    //< FLV 文件体 Tag 头（FLV Body Tag Header）。
    size_t flvbthpos;           //< FLVBTH 位置标记。
    FLVDemux::FLVBTD flvbtd;    //< FLV 文件体 Tag 数据（FLV Body Tag Data）。
    size_t flvbtdpos;           //< FLVBTD 位置标记。
    FLVDemux::FLVBPTS flvbpts;  //< FLV 文件体 上一 Tag 尺寸（FLV Body Previous Tag Size）。
    size_t cur {0};             //< 游标（Cursor）。

    while (true) {
        if (FLVDemux::IsFLVHeader(pck.data, pck.len)) {
            FLVDemux::ParseFLVHeader(flvh, pck.data, cur, pck.len);
            FLVDemux::ParseFLVBodyPreviousTagSize(flvbpts, pck.data, cur, pck.len);
            assert(0 == flvbpts.PreviousTagSize);

        } else if (FLVDemux::IsFLVBodyTagHeader(pck.data, pck.len)) {
            flvbthpos = cur;
            FLVDemux::ParseFLVBodyTagHeader(flvbth, pck.data, cur, pck.len);
            flvbtdpos = cur;
            FLVDemux::ParseFLVBodyTagData(flvbth, flvbtd, pck.data, cur, pck.len);
            cur = flvbtdpos + flvbth.DataSize;
            FLVDemux::ParseFLVBodyPreviousTagSize(flvbpts, pck.data, cur, pck.len);
            assert(cur - 4 - flvbthpos == flvbpts.PreviousTagSize);

        } else {
            envir() << "FLVDemuxADTSAudioUDPSourceHelper: Bad header, not FLV header nor FLV body tag header.\n";
            return;

        }

        assert(cur <= pck.len);
        if (cur < pck.len) continue;
        else               break;
    }
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
