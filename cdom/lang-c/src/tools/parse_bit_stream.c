/** \copyright The MIT License */
#include "parse_bit_stream.h"

#include <math.h>

static const size_t BYTE_SIZE = 8;

bool parse8bits(uint8_t * const result,
                const uint8_t * const data, const size_t len,
                const size_t bits_start, const size_t bits_end)
{
        if (!(
                0 < bits_end - bits_start &&
                bits_end - bits_start < 8 &&
                bits_end < len * BYTE_SIZE
                )) return false;

        uint64_t tmp;
        if (!parse64bits(&tmp, data, len, bits_start, bits_end))
                return false;
        *result = (uint8_t)tmp;

        return true;
}

bool parse16bits(uint16_t * const result,
                 const uint8_t * const data, const size_t len,
                 const size_t bits_start, const size_t bits_end)
{
        if (!(
                0 < bits_end - bits_start &&
                bits_end - bits_start < 16 &&
                bits_end < len * BYTE_SIZE
                )) return false;

        uint64_t tmp;
        if (!parse64bits(&tmp, data, len, bits_start, bits_end))
                return false;
        *result = (uint16_t)tmp;

        return true;
}

bool parse32bits(uint32_t * const result,
                 const uint8_t * const data, const size_t len,
                 const size_t bits_start, const size_t bits_end)
{
        if (!(
                0 < bits_end - bits_start &&
                bits_end - bits_start < 32 &&
                bits_end < len * BYTE_SIZE
                )) return false;

        uint64_t tmp;
        if (!parse64bits(&tmp, data, len, bits_start, bits_end))
                return false;
        *result = (uint32_t)tmp;

        return true;
}

static size_t the_byte_left_offset(const uint8_t the_bit_on_the_byte)
{
        return the_bit_on_the_byte / BYTE_SIZE  * BYTE_SIZE;
}

static size_t the_byte_right_offset(const uint8_t the_bit_on_the_byte)
{
        return the_byte_left_offset(the_bit_on_the_byte) + 7;
}

static const uint8_t BITS_MASK_TABLE[8][8] = {
        {0x80u, 0xC0u, 0xE0u, 0xF0u, 0xF8u, 0xFCu, 0xFEu, 0xFFu},
        {0x00u, 0x40u, 0x60u, 0x70u, 0x78u, 0x7Cu, 0x7Eu, 0x7Fu},
        {0x00u, 0x00u, 0x20u, 0x30u, 0x38u, 0x3Cu, 0x3Eu, 0x3Fu},
        {0x00u, 0x00u, 0x00u, 0x10u, 0x18u, 0x1Cu, 0x1Eu, 0x1Fu},
        {0x00u, 0x00u, 0x00u, 0x00u, 0x08u, 0x0Cu, 0x0Eu, 0x0Fu},
        {0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x04u, 0x06u, 0x07u},
        {0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x02u, 0x03u},
        {0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x01u}
};

bool parse64bits(uint8_t * const result,
                 const uint8_t * const data, const size_t len,
                 const size_t bits_start, const size_t bits_end)
{
        if (!(
                0 < bits_end - bits_start &&
                bits_end - bits_start < 64 &&
                bits_end < len * BYTE_SIZE
                )) return false;

        *result = 0uLL;

        size_t yl = the_byte_left_offset(bits_start);   // byte left (bit offset)
        size_t yr = the_byte_right_offset(bits_start);  // byte right
        size_t il;                                      // bit left
        size_t ir;                                      // bit right
        do {
                il = fmax(bits_start, yl);
                ir = fmin(yr, bits_end);
                *result |= (data[il / BYTE_SIZE]
                            & BITS_MASK_TABLE[il % BYTE_SIZE][ir % BYTE_SIZE]
                            ) << bits_end - ir;
                yl += BYTE_SIZE;
                yr += BYTE_SIZE;
        } while (yl <= bits_end);

        return true;
}
