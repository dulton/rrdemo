/**
 * \file
 * \brief hello, world
 * \author zhengrr
 * \date 2016-10-12
 * \copyright The MIT License
 */

/*============================================================================*
 * C++98
 *============================================================================*/
#if 199711L <= __cplusplus

#include <iostream>

/**
 * \brief 程序入口
 * \param argc 参数计数
 * \param argv 参数向量
 * \return 退出状态
 * \sa http://en.cppreference.com/cpp/language/main_function
 */
int main(int argc, char *argv[]) {
   std::cout << "hello, world" << std::endl;
   return 0;
}

#endif
