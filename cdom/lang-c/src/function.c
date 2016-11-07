/** \file
 *  \brief 函数.
 *  \sa <http://en.cppreference.com/w/c/language/functions>
 *  \sa <http://en.cppreference.com/w/c/language/inline>
 *  \sa <http://en.cppreference.com/w/c/language/_Noreturn>
 *  \author zhengrr
 *  \date 2016-10-17 – 27
 *  \copyright The MIT License
 */
#if 201112L <= __STDC_VERSION__
# include <stdnoreturn.h>
#endif

#if 199901L <= __STDC_VERSION__
inline static void inline_function(void)
{
}
#endif

#if 201112L <= __STDC_VERSION__
static noreturn noreturn_function(void)
{
}
#endif
