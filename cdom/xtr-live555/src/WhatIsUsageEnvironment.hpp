/** \file
 *  \brief UsageEnvironment是什么鬼.
 *  \sa <http://live555.com/liveMedia/doxygen/html/classUsageEnvironment.html>
 *  \author zhengrr
 *  \date 2016-10-24 – 11-1
 *  \copyright The MIT License
 */

#ifndef _RRDEMOCDOMLIVE555_WHATISCLASSUSAGEENVIRONMENT_HPP
#define _RRDEMOCDOMLIVE555_WHATISCLASSUSAGEENVIRONMENT_HPP

#include <live555/Boolean.hh>
#include <live555/NetCommon.h>
#include <live555/strDup.hh>
#include <live555/UsageEnvironment.hh>
#include <live555/UsageEnvironment_version.hh>

namespace rrdemo {
namespace cpp {
namespace live555 {

class TaskScheduler;  // 前置声明

/// 用户环境
class UsageEnvironment {
public:
    Boolean reclaim();
    TaskScheduler& taskScheduler() const { return fScheduler; }
    typedef char const* MsgString;

    virtual MsgString getResultMsg() const = delete;
    virtual void setResultMsg(
        MsgString msg) = delete;
    virtual void setResultMsg(
        MsgString msg1, MsgString msg2) = delete;
    virtual void setResultMsg(
        MsgString msg1, MsgString msg2, MsgString msg3) = delete;

    virtual void setResultErrMsg(MsgString msg, int err = 0) = delete;
    virtual void appendToResultMsg(MsgString msg) = delete;
    virtual void reportBackgroundError() = delete;
    virtual void internalError();
    virtual int getErrno() const = delete;

    virtual UsageEnvironment& operator<<(char const* str) = delete;
    virtual UsageEnvironment& operator<<(int i) = delete;
    virtual UsageEnvironment& operator<<(unsigned u) = delete;
    virtual UsageEnvironment& operator<<(double d) = delete;
    virtual UsageEnvironment& operator<<(void* p) = delete;

    void* liveMediaPriv;
    void* groupsockPriv;

protected:
    explicit UsageEnvironment(TaskScheduler& scheduler);
    virtual ~UsageEnvironment();

private:
    TaskScheduler& fScheduler;
};// class UsageEnvironment


typedef void TaskFunc(void* clientData);
typedef void* TaskToken;
typedef u_int32_t EventTriggerId;

/// 任务调度器
class TaskScheduler {
public:
    virtual ~TaskScheduler();

    virtual TaskToken scheduleDelayedTask(
        int64_t microseconds, TaskFunc* proc, void* clientData) = 0;
    virtual void unscheduleDelayedTask(TaskToken& prevTask) = 0;
    virtual void rescheduleDelayedTask(
        TaskToken& task, int64_t microseconds, TaskFunc* proc, void* clientData);

    typedef void BackgroundHandlerProc(void* clientData, int mask);

#define SOCKET_READABLE    (1<<1)
#define SOCKET_WRITABLE    (1<<2)
#define SOCKET_EXCEPTION   (1<<3)
    virtual void setBackgroundHandling(
        int socketNum, int conditionSet,
        BackgroundHandlerProc* handlerProc, void* clientData) = 0;
    void disableBackgroundHandling(int socketNum) {
        setBackgroundHandling(socketNum, 0, nullptr, nullptr);
    }
    virtual void moveSocketHandling(int oldSocketNum, int newSocketNum) = delete;
    virtual void doEventLoop(char volatile* watchVariable = nullptr) = delete;


    virtual EventTriggerId
        createEventTrigger(TaskFunc* eventHandlerProc) = delete;
    virtual void
        deleteEventTrigger(EventTriggerId eventTriggerId) = delete;
    virtual void
        triggerEvent(EventTriggerId eventTriggerId, void* clientData = nullptr) = delete;

    void turnOnBackgroundReadHandling(
        int socketNum, BackgroundHandlerProc* handlerProc, void* clientData) {
        setBackgroundHandling(socketNum, SOCKET_READABLE, handlerProc, clientData);
    }
    void turnOffBackgroundReadHandling(int socketNum) {
        disableBackgroundHandling(socketNum);
    }

    virtual void internalError();

protected:
    TaskScheduler(); // abstract base class
};// class TaskScheduler

}// namespace live555
}// namespace cpp
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_WHATISCLASSUSAGEENVIRONMENT_HPP
