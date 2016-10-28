/** \file
 *  \brief 随机(数).
 *  \sa <http://en.cppreference.com/w/c/numeric/random>
 *  \author zhengrr
 *  \date 2016-10-10 – 27
 *  \copyright The MIT License
 */
#include "def.h"

# include <stdlib.h>
# include <time.h>

static int pseudo_random_number(void)
{
        srand((unsigned) time(NULL));
        return rand();  // [0, RAND_MAX]
}
