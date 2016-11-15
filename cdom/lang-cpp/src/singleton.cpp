/** \file
 *  \brief 单例模式。
 *  \author zhengrr
 *  \date 2016-10-18 – 11-14
 *  \copyright The MIT License
 */
#include <mutex>

namespace {

/// 线程安全的惰性单例模式类。
class ThreadSafeLazySingleton {
public:
    explicit ThreadSafeLazySingleton(const ThreadSafeLazySingleton&) = delete;
    ThreadSafeLazySingleton& operator=(const ThreadSafeLazySingleton&) = delete;

    static ThreadSafeLazySingleton& Instance();

private:
    explicit ThreadSafeLazySingleton() {}

};// class ThreadSafeLazySingleton

ThreadSafeLazySingleton& ThreadSafeLazySingleton::Instance()
{
#if (201103L<=__cplusplus /*C++11*/) || \
    (defined(_MSC_VER) && 1900<=_MSCVER /*VS2015*/) || \
    (defined(__GNUC__) && (4<__GNUC__ || 4==__GNUC__ && 3<=__GNUC_MINOR__) /*GCC4.3*/)
    // [N2660](http://open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2660.htm)
    static ThreadSafeLazySingleton inst;
    return inst;
#else
    static ThreadSafeLazySingleton* instptr = nullptr;
    if (!instptr) {
        static std::mutex mutex;
        mutex.lock();
        if (!instptr)
            instptr = new ThreadSafeLazySingleton;
        mutex.unlock();
    }
    return *instptr;
#endif
};

}// namespace
