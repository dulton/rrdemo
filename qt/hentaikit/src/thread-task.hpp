/* ************************************************************************//*!
 * \file
 * \author zhengrr
 * \date 2016-3-3 ~ 7-18
 * \copyright The MIT License
 ******************************************************************************/

#ifndef THREAD_TASK_HPP
#define THREAD_TASK_HPP

#include <QObject>

namespace nsp {

class ThreadTask : public QObject {
   Q_OBJECT

private:
   explicit ThreadTask(const ThreadTask &) = delete;
   explicit ThreadTask(ThreadTask &&) = delete;
   ThreadTask &operator=(const ThreadTask &) = delete;
   ThreadTask &operator=(ThreadTask &&) = delete;

public:
   explicit ThreadTask(QObject *parent = nullptr);
   ~ThreadTask(void) = default;

public slots:
   void start(void);

signals:
   void completed(void);

};  // class ThreadTask

}  // namespace nsp

#endif  // THREAD_TASK_HPP
