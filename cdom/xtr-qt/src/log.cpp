/** \copyright The MIT License */
#include "log.hpp"

#include <QDateTime>
#include <QFileInfo>
#include <QMutex>
#include <QTextStream>

namespace rrdemo
{
namespace cdom
{
namespace qt
{

LoggingController::LoggingController(const QString &path,
                                                   const QtMsgType &level)
    : file{new QFile(path)}, level{level}
{
    file = new QFile(path);
    if (!file->open(QIODevice::WriteOnly | QIODevice::Append))
        Q_ASSERT(false);
}

LoggingController::~LoggingController()
{
    Q_CHECK_PTR(file);
    if (!file)
        return;

    file->close();
    delete file;
    file = nullptr;
}

LoggingController &LoggingController::Instance(
    const QString &path, const QtMsgType &level)
{
#if 201103L <= __cplusplus /*C++11*/ && (\
    defined(_MSC_VER) && 1900 <= _MSCVER /*VS2015*/ || \
    defined(__GNUC__) && (4 < __GNUC__ || 4 == __GNUC__ && 3 <= __GNUC_MINOR__) /*GCC4.3*/ \
)// [Dynamic Initialization and Destruction with Concurrency](http://open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2660.htm)
    static LoggingController inst(path, level);
    return inst;
#else
    static LoggingController *inst;
    if(!inst){
        static QMutex mutex;
        mutex.lock();
        if(!inst)
            inst = new LoggingController(path, level);
        mutex.unlock();
    }
    return *inst;
#endif
}

void LoggingController::Handler(QtMsgType type,
                                       const QMessageLogContext &context,
                                       const QString &message)
{
    if (type < Instance().level)
        return;

    Q_CHECK_PTR(Instance().file);
    if (!Instance().file)
        return;

    const QString timeStr{
        QDateTime::currentDateTime().toString("yyMMdd HH:mm:ss.zzz")};

    QString typeStr;
    switch (type) {
        case QtDebugMsg:
            typeStr = "[Debug]";
            break;
        case QtWarningMsg:
            typeStr = "[Warning]";
            break;
        case QtCriticalMsg:
            typeStr = "[Critical]";
            break;
        case QtFatalMsg:
            typeStr = "[*Fatal*]";
            break;
        case QtInfoMsg:
            typeStr = "[Info]";
            break;
        default:
            Q_ASSERT(false);
            break;
    }

    QString localStr;
    switch (type) {
        case QtDebugMsg:
            break;
        case QtWarningMsg:
            break;
        case QtCriticalMsg:
            //break;
        case QtFatalMsg:
            localStr = QString(" \t@%1:%2:%3")
                .arg(QFileInfo(context.file).fileName())
                .arg(context.line)
                .arg(context.function);
            break;
        case QtInfoMsg:
            break;
    }

    const QString output{
        QString("%1 %2 \t%3%4").arg(timeStr, typeStr, message, localStr)};

    static QMutex mutex;
    mutex.lock();

    QTextStream stream(Instance().file);
    stream << output << "\n";
    stream.flush();

    mutex.unlock();
}

}// namespace qt
}// namespace cdom
}// namespace rrdemo
