/**
 * \file
 * \brief 布尔型
 * \sa http://en.cppreference.com/w/c/language/type
 * \sa [stdbool.h](http://en.cppreference.com/w/c/types/boolean)
 * \author zhengrr
 * \date 2016-10-9 – 10-11
 * \copyright The MIT License
 */

/*============================================================================*
 * C89
 *============================================================================*/
#ifdef __STDC__

#define BOOL int
#define TRUE 1
#define FALSE 0

static void c89boolean(void) {
   BOOL flag;
   if (flag)
      flag = TRUE;
   if (!flag)
      flag = FALSE;
}

#endif// C89

/*============================================================================*
 * C99
 *============================================================================*/
#if 199901L <= __STDC_VERSION__

#include <stdbool.h>

static void c99boolean(void) {
   bool flag;
   if (flag)
      flag = true;
   if (!flag)
      flag = false;
}

#endif// C99
