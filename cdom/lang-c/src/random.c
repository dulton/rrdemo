/** \file
 *  \brief 随机(数).
 *  \author zhengrr
 *  \date 2016-10-10 – 31
 *  \copyright The MIT License
 */
#include "def.h"

# include <stdlib.h>
# include <time.h>

/** \brief 生成伪随机数.
 *  \return 伪随机数，范围为 [0, RAND_MAX].
 *  \sa <http://en.cppreference.com/w/c/numeric/random>
 */
static int pseudo_random_number(void)
{
        srand((unsigned) time(NULL));
        return rand();  // [0, RAND_MAX]
}
