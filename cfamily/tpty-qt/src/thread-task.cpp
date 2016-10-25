/* ************************************************************************//*!
 * \copyright The MIT License
 ******************************************************************************/

#include "thread-task.hpp"

namespace nsp {

ThreadTask::ThreadTask(QObject *parent) : QObject(parent) {}

void ThreadTask::start(void) {
   /* ... */
   emit completed();
}

}  // namespace nsp
