/**
 * \file
 * \brief 单例模式
 * \author zhengrr
 * \date 2016-10-18
 * \copyright The MIT License
 */

#ifndef RRDEMO_CPP_LANG_DZNP_SINGLETON_HPP
#define RRDEMO_CPP_LANG_DZNP_SINGLETON_HPP

namespace rrdemo {
namespace cpp {
namespace lang {

/**
 * \brief 单例
 */
class Singleton {
   explicit Singleton(const Singleton &) = delete;
   explicit Singleton(Singleton &&) = delete;
   Singleton &operator=(const Singleton &) = delete;

private:
   explicit Singleton(void) = default;
   //Singleton &operator=(Singleton &&) = default;
   ~Singleton(void) = default;

public:
   inline static Singleton &get_instance(void) { return *instance; }

private:
   static Singleton *const instance;

public:
   /* ... */

};// class Singleton

}// namespace lang
}// namespace cpp
}// namespace rrdemo

#endif// RRDEMO_CPP_LANG_DZNP_SINGLETON_HPP
