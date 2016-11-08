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

    /*
     * 议题: main return 还是 exit(), 还有 abort()
     * 
     * 使用 exit() 将不会触发 main 函数中局部对象的析构, 但静态对象与全局对象不受影响;
     * 使用 abort() 则不会触发任何对象的析构, 包括局部, 静态, 和全局对象.
     * 
     * 另见: <http://stackoverflow.com/questions/461449/return-statement-vs-exit-in-main>
     */
    return 0;
}
#endif
