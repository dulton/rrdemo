/** \file
 *  \brief 程序入口.
 *  \author zhengrr
 *  \date 2016-10-9 – 11-7
 *  \copyright The MIT License
 */
#include <stdlib.h>
#include <stdio.h>

#ifdef ENABLE_MAIN
/** \brief 程序入口.
 *  \param argc 参数计数.
 *  \param argv 参数向量.
 *  \return 退出状态.
 *  \sa <http://en.cppreference.com/c/language/main_function>
 */
int main(int argc, char *argv[])
{
        printf("hello, world\n");
        return EXIT_SUCCESS;
}
#endif
