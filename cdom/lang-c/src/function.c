/** \file
 *  \brief 函数.
 *  \sa <http://en.cppreference.com/w/c/language/functions>
 *  \sa <http://en.cppreference.com/w/c/language/inline>
 *  \sa <http://en.cppreference.com/w/c/language/_Noreturn>
 *  \author zhengrr
 *  \date 2016-10-17 – 27
 *  \copyright The MIT License
 */
#include "def.h"

#ifdef C11
# include <stdnoreturn.h>
#endif

#ifdef C99
inline static void inline_function(void)
{
}
#endif

#ifdef C11
static noreturn noreturn_function(void)
{
}
#endif
