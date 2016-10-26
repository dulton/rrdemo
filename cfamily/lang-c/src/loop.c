/** \file
 *  \brief 循环
 *  \sa <http://en.cppreference.com/w/c/language/do>
 *  \sa <http://en.cppreference.com/w/c/language/for>
 *  \sa <http://en.cppreference.com/w/c/language/while>
 *  \author zhengrr
 *  \date 2016-10-9 – 26
 *  \copyright The MIT License
 */
#include "def.h"

/** \brief 循环
 */
static void loop(void) {
   int i = 0;
   do {
      ++i;
      continue;
   } while (i < 9);


#ifdef C99
   for (int j = 0; j < 9; ++j) {
      continue;
   }
#else
   int j = 0;
   for (j = 0; j < 9; ++j) {
      continue;
   }
#endif


   int k = 0;
   while (k < 9) {
      --k;
      continue;
   }
}
