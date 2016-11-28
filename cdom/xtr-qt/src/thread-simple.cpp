/** \copyright The MIT License */
#include "thread-simple.hpp"

#include <QCoreApplication>
#include <QThread>

namespace rrdemo {
namespace cdom {
namespace qt {

void Task::task()
{
    qInfo("Task thread %p.", QThread::currentThreadId());
    Q_EMIT completed();
}

}// namespace qt
}// namespace cdom
}// namespace rrdemo

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[])
{
    using namespace rrdemo::cdom::qt;

    QCoreApplication app(argc, argv);
    qInfo("Main thread %p.", QThread::currentThreadId());

    Task *task {new Task};
    QThread *thread {new QThread(&app)};
    task->moveToThread(thread);

    QObject::connect(thread, &QThread::started, task, &Task::task);
    QObject::connect(task, &Task::completed, thread, &QThread::quit);
    QObject::connect(thread, &QThread::finished, task, &Task::deleteLater);
    QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();

    return app.exec();
}
#endif// ENTRY SWITCH
