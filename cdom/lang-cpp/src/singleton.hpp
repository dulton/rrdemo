/** \file
 *  \brief 单例(模式).
 *  \author zhengrr
 *  \date 2016-10-18 – 31
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMCPP_SINGLETON_HPP
#define _RRDEMOCDOMCPP_SINGLETON_HPP

#include "def.hpp"

namespace rrdemo {
namespace cdom {
namespace cpp {

/// 线程安全(的)惰性单例(模式).
class ThreadSafeLazySingleton {
public:
    ThreadSafeLazySingleton& operator=(const ThreadSafeLazySingleton&) = delete;
    ThreadSafeLazySingleton& operator=(ThreadSafeLazySingleton&&) = delete;

    static ThreadSafeLazySingleton& Instance();

private:
    explicit ThreadSafeLazySingleton() { }

};// class ThreadSafeLazySingleton

}// namespace cpp
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMCPP_SINGLETON_HPP
