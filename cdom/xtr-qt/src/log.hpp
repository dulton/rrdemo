/** \file
 *  \author zhengrr
 *  \date 2016-1-9 – 11-2
 *  \copyright The MIT License
 */

#ifndef _RRDEMOCDOMQT_LOG_HPP
#define _RRDEMOCDOMQT_LOG_HPP

#include <QString>
#include <QFile>

namespace rrdemo
{
namespace cdom
{
namespace qt
{

/// 内建日志控制器.
class LoggingController
{
public:
    /// 初始化.
    static void Initialize(const QString &logPath,
                           const QtMsgType &level = QtWarningMsg);

    /// 设定输出日志等级.
    static void SetLevel(const QtMsgType &level)
    {
        LoggingController::level = level;
    }

    /// 获取输出日志等级.
    static QtMsgType GetLevel() const
    {
        return LoggingController::level;
    }

    /// 日志处理器.
    /** \param type
     *  \param context
     *  \param message
     */
    static void Handler(QtMsgType type,
                        const QMessageLogContext &context,
                        const QString &message);

private:
    static QtMsgType level;  ///< 日志等级.

    /* -------------------------------------------------------------- *
     * 使用单例模式管理日志文件:
     * -------------------------------------------------------------- */
private:
    /// 获取单例实例.
    static LoggingController &Instance();

    /// 私有化构造函数.
    explicit LoggingController()
    {};

public:
    /// 禁用复制构造函数.
    explicit LoggingController(const LoggingController &) = delete;

    /// 禁用复制赋值操作符.
    LoggingController &operator=(const LoggingController &) = delete;

    /// 析构函数.
    ~LoggingController();

private:
    QFile *logFile{nullptr};  ///< (统一)日志文件.
    QFile *opLogFile{nullptr};  ///< 操作日志文件.
    QFile *sysLogFile{nullptr};  ///< 系统日志文件.
};

}// namespace qt
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMQT_LOG_HPP
