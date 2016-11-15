/** \file
 *  \sa <http://doc.qt.io/qt-5/qthread.html>
 *  \author zhengrr
 *  \date 2016-3-3 – 11-15
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMQT_THREADSIMPLE_HPP
#define _RRDEMOCDOMQT_THREADSIMPLE_HPP

#include <QObject>

namespace rrdemo {
namespace cdom {
namespace qt {

class Task : public QObject {
    Q_OBJECT

public:
    explicit Task(QObject *parent = nullptr) : QObject(parent) {}
    explicit Task(const Task &) = delete;
    explicit Task(Task &&) = delete;
    Task &operator=(const Task &) = delete;
    Task &operator=(Task &&) = delete;
    ~Task() = default;

public slots:
    void task();

signals:
    void completed();
};// class Task

}// namespace qt
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMQT_THREADSIMPLE_HPP
