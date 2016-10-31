/** \file
 *  \brief 布尔(型).
 *  \sa <http://en.cppreference.com/w/c/language/arithmetic_types#Boolean_type>
 *  \sa [stdbool.h](http://en.cppreference.com/w/c/types/boolean)
 *  \author zhengrr
 *  \date 2016-10-9 – 31
 *  \copyright The MIT License
 */
#include "def.h"

#ifdef C99
# include <stdbool.h>
#else
# define BOOL  int
# define TRUE  1
# define FALSE 0
#endif

static void boolean(void)
{
        /* 声明与定义 */
#ifdef C99
        bool flag = false;
#else
        BOOL flag = FALSE;
#endif

        /* 使用 */
        if (flag);

        if (!flag);
}
