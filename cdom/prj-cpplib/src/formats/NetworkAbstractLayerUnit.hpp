/** \file
 *  \author zhengrr
 *  \date 2016-12-22 – 2017-1-10
 *  \copyright The MIT License
 */
#ifndef RRDEMO__CDOM__LIVE555__NETWORK_ABSTRACT_LAYER_UNIT__HPP
#define RRDEMO__CDOM__LIVE555__NETWORK_ABSTRACT_LAYER_UNIT__HPP

#include <cstdint>

namespace rrdemo {
namespace cdom {
namespace live555 {

/// 网络抽象层单元头。
/** 因端序和实现差异导致的不可移植性，位域结构体仅供按字段访问，勿按内存整体访问。
 */
struct NALUHeader {
    union {
        uint32_t variation4bytes : 32;  ///< 起始码 4 字节变种，固为 00000001(16)；
        uint32_t variation3bytes : 24;  ///< 起始码 3 字节变种，固为 000001(16)。
    } start_codes;                   ///< 起始码；
    uint8_t forbidden_zero_bit : 1;  ///< 禁止位，固为 0；
    uint8_t nal_ref_idc : 2;         ///< 参考重要度；
    uint8_t nal_unit_type : 5;       ///< 网络抽象层单元类型。
};

/// 网络抽象层单元 辅助增强信息，nal_unit_type = 6。
struct NALUSupplementalEnhancementInformation {};

/// 网络抽象层单元 序列参数集，nal_unit_type = 7。
struct NALUSequenceParameterSet {
    uint8_t profile_idc : 8;
    uint8_t constraint_set0_flag : 1;
    uint8_t constraint_set1_flag : 1;
    uint8_t constraint_set2_flag : 1;
    uint8_t constraint_set3_flag : 1;
    uint8_t reserved_zero_4bits : 4;
    uint8_t level_idc : 8;
};

/// 网络抽象层单元 图片参数集，nal_unit_type = 8。
struct NALUPictureParameterSet {};

/// 网络抽象层单元。
struct NetworkAbstractLayerUnit {
    /// 检查输入数据是否符合 NALU Header。
    static bool IsHeader(const uint8_t * const data, const size_t length);

};//struct NetworkAbstractLayerUnit

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// RRDEMO__CDOM__LIVE555__NETWORK_ABSTRACT_LAYER_UNIT__HPP
