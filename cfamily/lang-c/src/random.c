/** \file
 *  \brief 随机（数）
 *  \sa http://en.cppreference.com/w/c/numeric/random
 *  \author zhengrr
 *  \date 2016-10-10
 *  \copyright The MIT License
 */
#include "def.h"

#ifdef C89
# include <stdlib.h>
# include <time.h>
#endif

#ifdef C89

/** \brief 生成伪随机数
 *  \details 使用 stdlib.h 中的伪随机数生成器，基于当前时间生成伪随机数。
 *  其范围在 [0, RAND_MAX]。
 */
static int generate_pseudo_random_number(void) {
   srand((unsigned) time(NULL));
   return rand();
}

#endif// C89
