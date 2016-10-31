/** \file
 *  \brief 数值(型).
 *  \sa <http://en.cppreference.com/w/c/language/arithmetic_types#Integer_types>
 *  \sa [limits.h](http://en.cppreference.com/w/c/types/limits)
 *  \sa [stdint.h](http://en.cppreference.com/w/c/types/integer)
 *  \author zhengrr
 *  \date 2016-10-9 – 10-27
 *  \copyright The MIT License
 */
#include "def.h"

#include <limits.h>
#ifdef C99
# include <stdint.h>
#endif

static void numeric(void)
{
        /* 声明与定义 */
        signed char signed_char = (signed char) 0;
        unsigned char unsigned_char = (unsigned char) 0;
        short signed_short_int = (short) 0;
        unsigned short unsigned_short_int = (unsigned short) 0;
        int signed_int = 0;
        unsigned unsigned_int = 0u;
        long signed_long_int = 0L;
        unsigned long unsigned_long_int = 0uL;
#ifdef C99
        long long signed_long_long_int = 0LL;
        unsigned long long unsigned_long_long_int = 0uLL;
        int8_t signed_exactly_8bit_int;
        int_fast8_t signed_least_8bit_fastest_int;
        int_least8_t signed_least_8bit_smallest_int;
        int16_t signed_exactly_16bit_int;
        int_fast16_t signed_least_16bit_fastest_int;
        int_least16_t signed_least_16bit_smallest_int;
        int32_t signed_exactly_32bit_int;
        int_fast32_t signed_least_32bit_fastest_int;
        int_least32_t signed_least_32bit_smallest_int;
        int64_t signed_exactly_64bit_int;
        int_fast64_t signed_least_64bit_fastest_int;
        int_least64_t signed_least_64bit_smallest_int;
#endif
}
