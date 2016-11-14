/** \file
 *  \brief 类。
 *  \sa <http://en.cppreference.com/w/cpp/language/classes>
 *  \author zhengrr
 *  \date 2016-10-19 – 11-14
 *  \copyright The MIT License
 */
namespace {

class Class {
public:
    /// 默认构造函数。
    /** \sa <http://en.cppreference.com/w/cpp/language/default_constructor>
     */
    explicit Class() = delete;

    /// 复制构造函数。
    /** \sa <http://en.cppreference.com/w/cpp/language/copy_constructor>
     */
    explicit Class(const Class&) = delete;

    /// 移动构造函数。
    /** \sa <http://en.cppreference.com/w/cpp/language/move_constructor>
     */
    explicit Class(Class&&) = delete;

    /// 析构函数。
    /** \sa <http://en.cppreference.com/w/cpp/language/destructor>
     */
    ~Class(void) = delete;

    /// 复制赋值操作符。
    /** \sa <http://en.cppreference.com/w/cpp/language/copy_assignment>
     */
    Class& operator=(const Class&) = delete;

    /// 移动赋值操作符。
    /** \sa <http://en.cppreference.com/w/cpp/language/move_assignment>
     */
    Class& operator=(Class&&) = delete;

};// class Class

}// namespace
