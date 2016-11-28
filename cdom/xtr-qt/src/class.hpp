/** \file
 *  \sa <http://doc.qt.io/qt-5/qobject.html#Q_OBJECT>
 *  \author zhengrr
 *  \date 2016-10-21 – 11-28
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMQT_CLASS_HPP
#define _RRDEMOCDOMQT_CLASS_HPP

#include <QObject>

namespace rrdemo {
namespace cdom {
namespace qt {

/// Qt 类。
/**
 */
class Class : public QObject {
    Q_OBJECT

public:
    explicit Class(QObject *parent = Q_NULLPTR);
    explicit Class(const Class &) Q_DECL_EQ_DELETE;
    explicit Class(Class &&) Q_DECL_EQ_DELETE;
    Class &operator=(const Class &)Q_DECL_EQ_DELETE;
    Class &operator=(Class &&)Q_DECL_EQ_DELETE;
    ~Class() Q_DECL_EQ_DEFAULT;
    
};// class Class

}// namespace qt
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMQT_CLASS_HPP
