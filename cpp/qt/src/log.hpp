/** \file
 *  \author zhengrr
 *  \date 2016-1-9 – 10-20
 *  \copyright The MIT License
 */

#ifndef _RRDEMOCPPQT_LOG_HPP
#define _RRDEMOCPPQT_LOG_HPP

#include <QString>

class QFile;
class QTextStream;

namespace rrdemo {
namespace cpp {
namespace qt {

/// 获取(输出)日志等级
QtMsgType getLogLevel(void);

/// 设定(输出)日志等级
void setLogLevel(const QtMsgType level);

/// 日志初始化
/** \param logPath 日志文件路径
 *  \param logLevel (输出)日志等级
 *  \post logDestroy
 */
void logInitialize(const QString &logPath = "log.txt",
                   const QtMsgType logLevel = QtWarningMsg);

/// 日志处理器
/** \param type
 *  \param context
 *  \param message
 *  \pre logInitialize
 *  \post logDestroy
 */
void logHandler(QtMsgType type,
                const QMessageLogContext &context,
                const QString &message);

/// 日志销毁
/** \pre logInitialize
 */
void logDestroy();

}// namespace qt
}// namespace cpp
}// namespace rrdemo

#endif// _RRDEMOCPPQT_LOG_HPP
