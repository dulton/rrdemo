/* ************************************************************************//*!
 * \copyright The MIT License
 ******************************************************************************/

#include <cassert>

#include <QThread>
#include <QTimer>

#include "thread-task.hpp"

namespace {

using namespace nsp;

static ThreadTask *task {nullptr};
static QThread *worker {nullptr};

void prep(void) {
   assert(!task && !worker);
   if (task || worker) return;

   task = new ThreadTask;
   worker = new QThread;
   task->moveToThread(worker);

   /* on task completed */
   QObject::connect(task, &ThreadTask::completed,
                    [](void) {
      /* ... */
   });

   /* on worker shutdown */
   QObject::connect(worker, &QThread::finished,
                    task, &ThreadTask::deleteLater);
   QObject::connect(worker, &QThread::finished,
                    worker, &QThread::deleteLater);

   worker->start();
};

void start(void) {
   assert(task);
   if (!task) return;

   QTimer::singleShot(0, task, &ThreadTask::start);
}

void shdn(void) {
   assert(worker);
   if (!worker) return;

   QTimer::singleShot(0, worker, &QThread::quit);
}

}  // namespace
