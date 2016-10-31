/** \copyright The MIT License */
#include "singleton.hpp"

#ifndef CPP11
# include <pthread.h>
#endif

namespace {

#ifndef CPP11
pthread_mutex_t thread_safe_lazy_singleton_mutex;
#endif

}// namespace

namespace rrdemo {
namespace cdom {
namespace cpp {

ThreadSafeLazySingleton& ThreadSafeLazySingleton::Instance()
{
#ifdef CPP11
    static ThreadSafeLazySingleton inst;
    return inst;
#else
    static ThreadSafeLazySingleton* inst = 0;
    if (!inst) {
        pthread_mutex_lock(&thread_safe_lazy_singleton_mutex);
        if (!inst)
            inst = new ThreadSafeLazySingleton();
        pthread_mutex_unlock(&thread_safe_lazy_singleton_mutex);
    }
#endif
};

}// namespace cpp
}// namespace cdom
}// namespace rrdemo
