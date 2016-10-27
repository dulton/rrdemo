/** \file
 *  \brief 循环.
 *  \sa <http://en.cppreference.com/w/c/language/do>
 *  \sa <http://en.cppreference.com/w/c/language/for>
 *  \sa <http://en.cppreference.com/w/c/language/while>
 *  \author zhengrr
 *  \date 2016-10-9 – 27
 *  \copyright The MIT License
 */
#include "def.h"

static void do_while_loop(void)
{
        int i = 0;
        do {
                ++i;
                continue;
        } while (i < 9);
}

static void for_loop(void)
{
#ifdef C99
        for (int i = 0; i < 9; ++i) {
                continue;
        }
#else
        int i = 0;
        for (i = 0; i < 9; ++i) {
           continue;
        }
#endif
}

static void while_loop(void)
{
        int i = 0;
        while (i < 9) {
                ++i;
                continue;
        }
}
