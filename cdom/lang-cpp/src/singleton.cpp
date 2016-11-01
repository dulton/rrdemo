/** \copyright The MIT License */
#include "singleton.hpp"

#include <mutex>  // C++11 mutex, just as an example.

namespace rrdemo {
namespace cdom {
namespace cpp {

ThreadSafeLazySingleton& ThreadSafeLazySingleton::Instance()
{
#if 201103L<=__cplusplus /*C++11*/ && (\
    defined(_MSC_VER) && 1900<=_MSCVER /*VS2015*/ || \
    defined(__GNUC__) && (4<__GNUC__ || 4==__GNUC__ && 3<=__GNUC_MINOR__) /*GCC4.3*/ \
)// [Dynamic Initialization and Destruction with Concurrency](http://open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2660.htm)
    static ThreadSafeLazySingleton inst;
    return inst;
#else
    static ThreadSafeLazySingleton* inst = nullptr;
    if (!inst) {
        static std::mutex mutex;
        mutex.lock();
        if (!inst)
            inst = new ThreadSafeLazySingleton;
        mutex.unlock();
    }
    return *inst;
#endif
};

}// namespace cpp
}// namespace cdom
}// namespace rrdemo
