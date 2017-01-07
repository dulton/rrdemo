/** \file
 *  \author zhengrr
 *  \data 2017-1-6
 *  \copyright The MIT License
 */
#ifndef RRDEMO__CDOM__C__PARSE_BIT_STREAM__H
#define RRDEMO__CDOM__C__PARSE_BIT_STREAM__H

#include <inttypes.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

        /** \brief 解析最长 8 个位。
         *  \brief[out] result     解析结果；
         *  \brief[in]  data       数据；
         *  \brief[in]  len        数据长度；
         *  \brief[in]  bits_start 位起点偏移量；
         *  \brief[in]  bits_end   位终点偏移量。
         *  \return 解析状态，true 表示成功，false 表示失败。
         */
        bool parse8bits(uint8_t * const result,
                        const uint8_t * const data, const size_t len,
                        const size_t bits_start, const size_t bits_end);

        /** \brief 解析最长 16 个位。
         *  \brief[out] result     解析结果；
         *  \brief[in]  data       数据；
         *  \brief[in]  len        数据长度；
         *  \brief[in]  bits_start 位起点偏移量；
         *  \brief[in]  bits_end   位终点偏移量。
         *  \return 解析状态，true 表示成功，false 表示失败。
         */
        bool parse16bits(uint16_t * const result,
                         const uint8_t * const data, const size_t len,
                         const size_t bits_start, const size_t bits_end);

        /** \brief 解析最长 32 个位。
         *  \brief[out] result     解析结果；
         *  \brief[in]  data       数据；
         *  \brief[in]  len        数据长度；
         *  \brief[in]  bits_start 位起点偏移量；
         *  \brief[in]  bits_end   位终点偏移量。
         *  \return 解析状态，true 表示成功，false 表示失败。
         */
        bool parse32bits(uint32_t * const result,
                         const uint8_t * const data, const size_t len,
                         const size_t bits_start, const size_t bits_end);

        /** \brief 解析最长 64 个位。
         *  \brief[out] result     解析结果；
         *  \brief[in]  data       数据；
         *  \brief[in]  len        数据长度；
         *  \brief[in]  bits_start 位起点偏移量；
         *  \brief[in]  bits_end   位终点偏移量。
         *  \return 解析状态，true 表示成功，false 表示失败。
         */
        bool parse64bits(uint64_t * const result,
                         const uint8_t * const data, const size_t len,
                         const size_t bits_start, const size_t bits_end);

#ifdef __cplusplus
}
#endif

#endif// RRDEMO__CDOM__C__PARSE_BIT_STREAM__H