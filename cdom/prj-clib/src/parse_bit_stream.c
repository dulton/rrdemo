/** \copyright The MIT License */
#include "parse_bit_stream.h"

#include <math.h>

static const size_t BYTE_BITS = 8;

static size_t the_byte_left_offset(const size_t the_bit_on_the_byte)
{
        return the_bit_on_the_byte / BYTE_BITS * BYTE_BITS;  // 整型的除法截断。
}

static size_t the_byte_right_offset(const size_t the_bit_on_the_byte)
{
        return the_byte_left_offset(the_bit_on_the_byte) + 7;
}

static const uint8_t BITS_MASK_TABLE[8][8] = {
        {0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF},
        {0x00, 0x40, 0x60, 0x70, 0x78, 0x7C, 0x7E, 0x7F},
        {0x00, 0x00, 0x20, 0x30, 0x38, 0x3C, 0x3E, 0x3F},
        {0x00, 0x00, 0x00, 0x10, 0x18, 0x1C, 0x1E, 0x1F},
        {0x00, 0x00, 0x00, 0x00, 0x08, 0x0C, 0x0E, 0x0F},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x06, 0x07},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01}
};

bool parse_bits(uintmax_t * const result,
                const uint8_t * const data, const size_t len,
                const size_t bits_start, const size_t bits_end)
{
        if (!(bits_start < bits_end)) return false;
        if (!(bits_end - bits_start < sizeof(uintmax_t) * BYTE_BITS)) return false;
        if (!(bits_end < len * BYTE_BITS)) return false;
        *result = 0;
        size_t BL = the_byte_left_offset(bits_start);   // Byte Left (Offset)
        size_t BR = the_byte_right_offset(bits_start);
        size_t bl;                                      // bit left (offset)
        size_t br;
        do {
                bl = (size_t)fmax(bits_start, BL);
                br = (size_t)fmin(BR, bits_end);
                *result |= (data[bl / BYTE_BITS] &
                            BITS_MASK_TABLE[bl % BYTE_BITS][br % BYTE_BITS]
                            ) << (bits_end - br);
                BL += BYTE_BITS;
                BR += BYTE_BITS;
        } while (BR <= bits_end);
        return true;
}

bool zrr_parse8bits(uint8_t * const result,
                    const uint8_t * const data, const size_t len,
                    const size_t bits_start, const size_t bits_end)
{
        if (!(bits_start < bits_end)) return false;
        if (!(bits_end - bits_start < sizeof(uint8_t) * BYTE_BITS)) return false;
        if (!(bits_end < len * BYTE_BITS)) return false;
        uintmax_t tmp;
        if (!parse_bits(&tmp, data, len, bits_start, bits_end)) return false;
        *result = (uint8_t)tmp;
        return true;
}

bool zrr_parse16bits(uint16_t * const result,
                     const uint8_t * const data, const size_t len,
                     const size_t bits_start, const size_t bits_end)
{
        if (!(bits_start < bits_end)) return false;
        if (!(bits_end - bits_start < sizeof(uint16_t) * BYTE_BITS)) return false;
        if (!(bits_end < len * BYTE_BITS)) return false;
        uintmax_t tmp;
        if (!parse_bits(&tmp, data, len, bits_start, bits_end)) return false;
        *result = (uint16_t)tmp;
        return true;
}

bool zrr_parse32bits(uint32_t * const result,
                     const uint8_t * const data, const size_t len,
                     const size_t bits_start, const size_t bits_end)
{
        if (!(bits_start < bits_end)) return false;
        if (!(bits_end - bits_start < sizeof(uint32_t) * BYTE_BITS)) return false;
        if (!(bits_end < len * BYTE_BITS)) return false;
        uintmax_t tmp;
        if (!parse_bits(&tmp, data, len, bits_start, bits_end)) return false;
        *result = (uint32_t)tmp;
        return true;
}

bool zrr_parse64bits(uint64_t * const result,
                     const uint8_t * const data, const size_t len,
                     const size_t bits_start, const size_t bits_end)
{
        if (!(bits_start < bits_end)) return false;
        if (!(bits_end - bits_start < sizeof(uint64_t) * BYTE_BITS)) return false;
        if (!(bits_end < len * BYTE_BITS)) return false;
        uintmax_t tmp;
        if (!parse_bits(&tmp, data, len, bits_start, bits_end)) return false;
        *result = (uint64_t)tmp;
        return true;
}
