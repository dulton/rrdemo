/** \file
 *  \brief 线程.
 *  \author zhengrr
 *  \date 2016-11-7
 *  \copyright The MIT License
 */
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

namespace {

void ThreadAlpha()
{
    /* 因 std::cout 仅保证单个 << 操作的原子性, 所以此处使用 "\n" 而非 << std::endl.
     * 见 ISO/IEC 14882:2011 (C++ 11) §27.4.1.
     */
    std::cout << "ThreadAlpha: Thread alpha are called.\n";
}

void ThreadBeta()
{
    std::cout << "ThreadBeta: Thread beta are called.\n";
}

}// namespace

#ifndef ENABLE_THREAD_MAIN
int main()
{
    std::cout << "main: Call ThreadAlpha.\n";
    std::thread alpha(ThreadAlpha);
    std::cout << "main: Call ThreadBeta.\n";
    std::thread beta(ThreadBeta);

    std::cout << "main: Wait for thread alpha finishes.\n";
    alpha.join();
    std::cout << "main: Thread alpha are finished.\n";
    std::cout << "main: Wait for thread beta finishes.\n";
    beta.join();
    std::cout << "main: Thread beta are finished.\n";

    return 0;
}
#endif
