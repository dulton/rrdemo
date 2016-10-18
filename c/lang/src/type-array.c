/**
 * \file
 * \brief 数组
 * \sa http://en.cppreference.com/w/c/language/array
 * \sa http://en.cppreference.com/w/c/language/array_initialization
 * \author zhengrr
 * \date 2016-10-9 – 10-11
 * \copyright The MIT License
 */
#include "def.h"

static void init(void) {
#ifdef C89
   int a[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; /* 1, 2, 3, 4, 5, 6, 7, 8, 9 */
   int b[9] = {1, 2, 3};                   /* 1, 2, 3, 0, 0, 0, 0, 0, 0 */
   int c[9] = {0};                         /* 0, 0, 0, 0, 0, 0, 0, 0, 0 */
   int d[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};  /* 1, 2, 3, 4, 5, 6, 7, 8, 9 */
#endif

#ifdef C99
   int e[10] = {[1] = 2, [3] = 4};         /* 0, 2, 0, 4, 0, 0, 0, 0, 0 */
#endif
}
