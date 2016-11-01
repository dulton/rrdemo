/** \file
 *  \author zhengrr
 *  \date 2016-1-9 – 11-1
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
private:
    /// 私有化构造函数.
    explicit LoggingController(const QString &path, const QtMsgType &level);
public:
    /// 禁用复制构造函数.
    explicit LoggingController(const LoggingController &) = delete;
    /// 禁用复制赋值操作符.
    LoggingController &operator=(const LoggingController &) = delete;
    /// 析构函数.
    ~LoggingController();

    /// 初始化.
    static void Initialize(const QString &logPath = "log.txt",
                           const QtMsgType &level = QtWarningMsg);

    /// 获取单例实例.
    static LoggingController &Instance(const QString &path = "log.txt",
                                       const QtMsgType &level = QtWarningMsg);

    /// 设定输出日志等级.
    static void SetLevel(const QtMsgType &level)
    {
        Instance().level = level;
    }

    /// 获取输出日志等级.
    static QtMsgType GetLevel() const
    {
        return Instance().level;
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
    bool initialized{false};
    QFile *file{nullptr};
    QtMsgType level;
};

}// namespace qt
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMQT_LOG_HPP
