/** \file
 *  \brief 程序入口.
 *  \author zhengrr
 *  \date 2016-10-12 – 11-7
 *  \copyright The MIT License
 */
#include <iostream>

#ifdef ENABLE_MAIN
/// 程序入口.
/** \param argc 参数计数.
 *  \param argv 参数向量.
 *  \return 退出状态.
 *  \sa <http://en.cppreference.com/cpp/language/main_function>
 */
int main(int argc, char* argv[])
{
    std::cout << "hello, world" << std::endl;
    return 0;
}
#endif
