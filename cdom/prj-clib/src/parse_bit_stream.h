/** \file
 *  \brief 解析位流（bit stream）。
 *  \author zhengrr
 *  \data 2017-1-6 – 12
 *  \copyright The MIT License
 */
#ifndef RRDEMO__CDOM__C_LIBRARY__PARSE_BIT_STREAM__H
#define RRDEMO__CDOM__C_LIBRARY__PARSE_BIT_STREAM__H

#include <stdint.h>
#include <stdbool.h>

#include "api.h"

#ifdef __cplusplus
extern "C" {
#endif

        /** \brief 解析最长 8 个位（bit(s)）。
         *  \param[out] result     解析结果；
         *  \param[in]  data       数据；
         *  \param[in]  len        数据长度（byte(s)）；
         *  \param[in]  bits_start 位起点偏移量（bit）；
         *  \param[in]  bits_end   位终点偏移量（bit）。
         *  \return 成功与否。
         */
        RRDEMO__CDOM__C_LIBRARY__API bool zrr_parse8bits(
                uint8_t * const result,
                const uint8_t * const data, const size_t len,
                const size_t bits_start, const size_t bits_end);

        /** \brief 解析最长 16 个位（bit(s)）。
         *  \param[out] result     解析结果；
         *  \param[in]  data       数据；
         *  \param[in]  len        数据长度（byte(s)）；
         *  \param[in]  bits_start 位起点偏移量（bit）；
         *  \param[in]  bits_end   位终点偏移量（bit）。
         *  \return 成功与否。
         */
        RRDEMO__CDOM__C_LIBRARY__API bool zrr_parse16bits(
                uint16_t * const result,
                const uint8_t * const data, const size_t len,
                const size_t bits_start, const size_t bits_end);

        /** \brief 解析最长 32 个位（bit(s)）。
         *  \param[out] result     解析结果；
         *  \param[in]  data       数据；
         *  \param[in]  len        数据长度（byte(s)）；
         *  \param[in]  bits_start 位起点偏移量（bit）；
         *  \param[in]  bits_end   位终点偏移量（bit）。
         *  \return 成功与否。
         */
        RRDEMO__CDOM__C_LIBRARY__API bool zrr_parse32bits(
                uint32_t * const result,
                const uint8_t * const data, const size_t len,
                const size_t bits_start, const size_t bits_end);

        /** \brief 解析最长 64 个位（bit(s)）。
         *  \param[out] result     解析结果；
         *  \param[in]  data       数据；
         *  \param[in]  len        数据长度（byte(s)）；
         *  \param[in]  bits_start 位起点偏移量（bit）；
         *  \param[in]  bits_end   位终点偏移量（bit）。
         *  \return 成功与否。
         */
        RRDEMO__CDOM__C_LIBRARY__API bool zrr_parse64bits(
                uint64_t * const result,
                const uint8_t * const data, const size_t len,
                const size_t bits_start, const size_t bits_end);

#ifdef __cplusplus
}
#endif

#endif// RRDEMO__CDOM__C_LIBRARY__PARSE_BIT_STREAM__H
