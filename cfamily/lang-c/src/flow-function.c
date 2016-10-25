/** \file
 *  \brief 函数
 *  \sa <http://en.cppreference.com/w/c/language/functions>
 *  \author zhengrr
 *  \date 2016-10-17
 *  \copyright The MIT License
 */
#include "def.h"

#ifdef C11
#   include <stdnoreturn.h>
#endif

#ifdef C99

/** \brief 内联函数
 *  \sa <http://en.cppreference.com/w/c/language/inline>
 *  \since C99
 */
inline static void inline_function(void)
{
}

#endif// C99

#ifdef C11

/** \brief 不返回函数
 *  \sa <http://en.cppreference.com/w/c/language/_Noreturn>
 *  \since C11
 */
static noreturn noreturn_function(void)
{
}

#endif// C11
