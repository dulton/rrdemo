/**
 * \file
 * \brief hello, world
 * \sa [Compilers Predefined Macros](http://sf.net/p/predef/wiki/Compilers/)
 * \sa [OSs Predefined Macros](http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system)
 * \sa [GCC Predefined Macros](http://gcc.gnu.org/onlinedocs/cpp/Predefined-Macros.html)
 * \sa [MSVC Predefined Macros](http://msdn.microsoft.com/library/b0084kay.aspx)
 * \author zhengrr
 * \date 2016-10-9 – 10-12
 * \copyright The MIT License
 */

/*============================================================================*
 * C89
 *============================================================================*/
#ifdef __STDC__

#include <stdlib.h>
#include <stdio.h>

/**
 * \brief 程序入口
 * \param argc 参数计数
 * \param argv 参数向量
 * \return 退出状态
 * \sa http://en.cppreference.com/c/language/main_function
 */
int main(int argc, char *argv[]) {
   printf("hello, world\n");
   return EXIT_SUCCESS;
}

#endif// C89
