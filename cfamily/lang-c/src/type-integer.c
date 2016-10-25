/**
 * \file
 * \brief 整型
 * \sa <http://en.cppreference.com/w/c/language/arithmetic_types#Integer_types>
 * \sa [limits.h](http://en.cppreference.com/w/c/types/limits)
 * \sa [stdint.h](http://en.cppreference.com/w/c/types/integer)
 * \author zhengrr
 * \date 2016-10-9 – 10-17
 * \copyright The MIT License
 */
#include "def.h"

#ifdef C89
#   include <limits.h>
#endif
#ifdef C99
#   include <stdint.h>
#endif

static void init(void) {
#ifdef C89
   signed char signed_char = (signed char) 0;
   unsigned char unsigned_char = (unsigned char) 0;

   short signed_short_int = (short) 0;
   unsigned short unsigned_short_int = (unsigned short) 0;

   int signed_int = 0;
   unsigned unsigned_int = 0u;

   long signed_long_int = 0L;
   unsigned long unsigned_long_int = 0uL;
#endif

#ifdef C99
   long long signed_long_long_int = 0LL;
   unsigned long long unsigned_long_long_int = 0uLL;

   /* 定宽整型 */
   int8_t signed_exactly8bit_int;
   int_fast8_t signed_least8bitfastest_int;
   int_least8_t signed_least8bitsmallest_int;

   int16_t signed_exactly16bit_int;
   int_fast16_t signed_least16bitfastest_int;
   int_least16_t signed_least16bitsmallest_int;

   int32_t signed_exactly32bit_int;
   int_fast32_t signed_least32bitfastest_int;
   int_least32_t signed_least32bitsmallest_int;

   int64_t signed_exactly64bit_int;
   int_fast64_t signed_least64bitfastest_int;
   int_least64_t signed_least64bitsmallest_int;
#endif
}
