/** \copyright The MIT License */
#include "WhatIsUsageEnvironment.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

Boolean UsageEnvironment::reclaim() const {
    if (!liveMediaPriv && !groupsockPriv) {
        delete this;
        return True;
    }

    return False;
}

UsageEnvironment::UsageEnvironment(TaskScheduler& scheduler)
    : liveMediaPriv(nullptr), groupsockPriv(nullptr), fScheduler(scheduler) {}

UsageEnvironment::~UsageEnvironment() {}

void UsageEnvironment::internalError() {
    abort();
}

TaskScheduler::TaskScheduler() {}

TaskScheduler::~TaskScheduler() {}

void TaskScheduler::rescheduleDelayedTask(TaskToken& task,
                                          int64_t microseconds, TaskFunc* proc,
                                          void* clientData) {
    unscheduleDelayedTask(task);
    task = scheduleDelayedTask(microseconds, proc, clientData);
}

void TaskScheduler::internalError() {
    abort();
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
