/**
 * \file
 * \brief for 循环
 * \sa <http://en.cppreference.com/w/c/language/for>
 * \author zhengrr
 * \date 2016-10-9 – 17
 * \copyright The MIT License
 */
#include "def.h"

/**
 * \brief for 循环
 */
static void for_loop(void) {
#if defined C99
   for (int i = 0; i < 9; ++i) {
      continue;
   }
#elif defined C98
   int i = 0;
   for (i = 0; i < 9; ++i) {
      continue;
   }
#endif
}
