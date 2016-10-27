/** \file
 *  \brief 数组.
 *  \sa <http://en.cppreference.com/w/c/language/array>
 *  \sa <http://en.cppreference.com/w/c/language/array_initialization>
 *  \author zhengrr
 *  \date 2016-10-9 – 10-27
 *  \copyright The MIT License
 */
#include "def.h"

static void declaring_and_defining(void)
{
        int a[3] = {1, 2, 3};           // 1, 2, 3
        int b[3] = {1, 2};              // 1, 2, 0
        int c[3] = {0};                 // 0, 0, 0
        int d[ ] = {1, 2, 3};           // 1, 2, 3
#ifdef C99
        int e[3] = {[0] = 1, [2] = 3};  // 1, 0, 3
#endif
}
