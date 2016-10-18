/**
 * \file
 * \brief 布尔型
 * \sa <http://en.cppreference.com/w/c/language/arithmetic_types#Boolean_type>
 * \sa [stdbool.h](http://en.cppreference.com/w/c/types/boolean)
 * \author zhengrr
 * \date 2016-10-9 – 17
 * \copyright The MIT License
 */
#include "def.h"

#if defined C99
#   include <stdbool.h>
#elif defined C89
#   define BOOL  int
#   define TRUE  1
#   define FALSE 0
#endif

static void boolean(void) {
   /* definition */
#if defined C99
   bool flag;
#elif defined C89
   BOOL flag;
#endif

   /* if true */
   if (flag)
      ;

   /* if false */
   if (!flag)
      ;
}

#endif// C99
