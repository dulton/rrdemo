/* ************************************************************************//*!
 * \file
 * \author zhengrr
 * \date 2016-1-9 ~ 7-18
 * \copyright The MIT License
 ******************************************************************************/

#ifndef LOG_HPP
#define LOG_HPP

#include <QString>

class QFile;
class QTextStream;

namespace nsp {

/* ****************************************************//*!
 * \brief Get 'logLevel'
 **********************************************************/
const QtMsgType getLogLevel(void);

/* ****************************************************//*!
 * \brief Set 'logLevel'
 **********************************************************/
void setLogLevel(const QtMsgType level);

/* ****************************************************//*!
 * \post logDstr
 **********************************************************/
void logInit(const QString &logPath = "log.txt",
             const QtMsgType logLevel = QtMsgType::QtWarningMsg);

/* ****************************************************//*!
 * \pre logInit
 * \post LogDstr
 **********************************************************/
void logHandler(QtMsgType type,
                const QMessageLogContext &context,
                const QString &msg);

/* ****************************************************//*!
 * \pre logInit
 **********************************************************/
void logDstr(void);

}  // namespace nsp

#endif  // LOG_HPP
