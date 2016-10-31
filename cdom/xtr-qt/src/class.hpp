/** \file
 *  \author zhengrr
 *  \date 2016-10-21
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMQT_CLASS_HPP
#define _RRDEMOCDOMQT_CLASS_HPP

#include <QObject>

namespace rrdemo
{
namespace cdom
{
namespace qt
{

/// Qt类.
/**
 */
class Class: public QObject
{
Q_OBJECT

public:
    explicit Class(QObject *parent = nullptr);
    explicit Class(const Class &) = delete;
    explicit Class(Class &&) = delete;
    Class &operator=(const Class &) = delete;
    Class &operator=(Class &&) = delete;
    ~Class() = default;

};// class Class

}// namespace qt
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMQT_CLASS_HPP
