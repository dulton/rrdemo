/**
 * \file
 * \sa <http://en.cppreference.com/w/cpp/language/classes>
 * \author zhengrr
 * \date 2016-10-19
 * \copyright The MIT License
 */

#ifndef RRDEMO_CPP_LANG_CLASS_HPP
#define RRDEMO_CPP_LANG_CLASS_HPP

namespace rrdemo {
namespace cpp {
namespace lang {

class Class {
public:
   /**
    * \brief 默认构造函数
    * \sa <http://en.cppreference.com/w/cpp/language/default_constructor>
    */
   explicit Class() = delete;

   /**
    * \brief 复制构造函数
    * \sa <http://en.cppreference.com/w/cpp/language/copy_constructor>
    */
   explicit Class(const Class &) = delete;

   /**
    * \brief 移动构造函数
    * \sa <http://en.cppreference.com/w/cpp/language/move_constructor>
    */
   explicit Class(Class &&) = delete;

   /**
    * \brief 析构函数
    * \sa <http://en.cppreference.com/w/cpp/language/destructor>
    */
   ~Class(void) = delete;

   /**
    * \brief 复制赋值操作符
    * \sa <http://en.cppreference.com/w/cpp/language/copy_assignment>
    */
   Class &operator=(const Class &) = delete;

   /**
    * \brief 移动赋值操作符
    * \sa <http://en.cppreference.com/w/cpp/language/move_assignment>
    */
   Class &operator=(Class &&) = delete;

};// class Class

}// namespace lang
}// namespace cpp
}// namespace rrdemo

#endif// RRDEMO_CPP_LANG_CLASS_HPP
