/**
 * \file
 * \brief 整型
 * \sa http://en.cppreference.com/w/c/language/type
 * \sa [limits.h](http://en.cppreference.com/w/c/types/limits)
 * \sa [stdint.h](http://en.cppreference.com/w/c/types/integer)
 * \author zhengrr
 * \date 2016-10-9 – 10-11
 * \copyright The MIT License
 */

/*============================================================================*
 * C89                                                                        *
 *============================================================================*/
#ifdef __STDC__

#include <limits.h>

static void c89init(void) {
   short signed_short_int = (short) 0;
   unsigned short unsigned_short_int = (unsigned short) 0;

   int signed_int = 0;
   unsigned unsigned_int = 0u;

   long signed_long_int = 0L;
   unsigned long unsigned_long_int = 0uL;
}

#endif// C89

/*============================================================================*
 * C99                                                                        *
 *============================================================================*/
#if 199901L <= __STDC_VERSION__

#include <stdint.h>

static void c99init(void) {
   long long signed_long_long_int = 0LL;
   unsigned long long unsigned_long_long_int = 0uLL;
}

#endif// C99
