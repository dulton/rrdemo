/** \file
 *  \brief 循环.
 *  \author zhengrr
 *  \date 2016-10-9 – 31
 *  \copyright The MIT License
 */

/** \brief do–while 循环.
 *  \sa <http://en.cppreference.com/w/c/language/do>
 */
static void do_while_loop(void)
{
        int i = 0;
        do {
                ++i;
                continue;
        } while (i < 9);
}

/** \brief for 循环.
 *  \sa <http://en.cppreference.com/w/c/language/for>
 */
static void for_loop(void)
{
#if 199901L <= __STDC_VERSION__
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

/** \brief while 循环.
 *  \sa <http://en.cppreference.com/w/c/language/while>
 */
static void while_loop(void)
{
        int i = 0;
        while (i < 9) {
                ++i;
                continue;
        }
}
