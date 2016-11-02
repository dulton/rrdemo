/** \copyright The MIT License */
#include "log.hpp"

#include <QDateTime>
#include <QDir>
#include <QMutex>
#include <QTextStream>

namespace rrdemo
{
namespace cdom
{
namespace qt
{

void LoggingController::Initialize(const QString &logPath,
                                   const QtMsgType &level)
{
    Q_ASSERT(!Instance().logFile);
    if (Instance().logFile) return;

    /* 以 PATH/NAME-yyMMddHHmmsszzz(n).SUFFIX 的形式生成日志文件: */
    QFileInfo rfi(logPath);  // raw file info
    Q_ASSERT(rfi.isFile());
    if (!rfi.isFile()) return;
    QString dir{rfi.dir().path()};  // (raw) dir
    if (!dir.isEmpty()) dir.append("/");
    QString name{rfi.baseName()};  // (raw) name
    QString suffix{rfi.completeSuffix()};  // (raw) suffix
    if (!suffix.isEmpty()) suffix.insert(0, ".");

    QString time{QDateTime::currentDateTime().toString("yyMMddHHmmsszzz")};

    QString newPath{dir + name + time + suffix};
    if (QFileInfo::exists(newPath)) {
        for (int n = 0; QFileInfo::exists(newPath); ++n)
            newPath = dir + name + time + "(" + n + ")" + suffix;
    }

    Instance().logFile = new QFile(newPath);
    Instance().logFile->open(QIODevice::WriteOnly | QIODevice::Append);

    qInstallMessageHandler(Handler);
}

void LoggingController::Handler(QtMsgType type,
                                const QMessageLogContext &context,
                                const QString &message)
{
    if (type < Instance().level)
        return;

    Q_ASSERT(Instance().logFile);
    if (!Instance().logFile) return;

    QString time{QDateTime::currentDateTime().toString("yyMMdd HH:mm:ss.zzz")};

    QString t;
    switch (type) {
        case QtDebugMsg:
            t = "[D]";
            break;
        case QtWarningMsg:
            t = "[W]";
            break;
        case QtCriticalMsg:
            t = "[C]";
            break;
        case QtFatalMsg:
            t = "[F]";
            break;
        case QtInfoMsg:
            t = "[I]";
            break;
    }

    QString local;
    switch (type) {
        case QtDebugMsg:
            break;
        case QtWarningMsg:
            break;
        case QtCriticalMsg:  // break through
        case QtFatalMsg:
            local = QString("%1:%2:%3")
                .arg(QFileInfo(context.file).fileName())
                .arg(context.line)
                .arg(context.function);
            break;
        case QtInfoMsg:
            break;
    }

    static QMutex mutex;
    mutex.lock();
    QTextStream stream(Instance().logFile);
    stream << QString("%1 %2 %3 @%4").arg(time, t, message, local) << "\n";
    stream.flush();
    mutex.unlock();
}

LoggingController &LoggingController::Instance()
{
#if 201103L <= __cplusplus /*C++11*/ && (\
    defined(_MSC_VER) && 1900 <= _MSCVER /*VS2015*/ || \
    defined(__GNUC__) && (4 < __GNUC__ || 4 == __GNUC__ && 3 <= __GNUC_MINOR__) /*GCC4.3*/ \
)// [Dynamic Initialization and Destruction with Concurrency](http://open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2660.htm)
    static LoggingController inst;
    return inst;
#else
    static LoggingController *inst;
    if(!inst){
        static QMutex mutex;
        mutex.lock();
        if(!inst)
            inst = new LoggingController;
        mutex.unlock();
    }
    return *inst;
#endif
}

LoggingController::~LoggingController()
{
    if (!logFile) {
        logFile->close();
        delete logFile;
        logFile = nullptr;
    }

    if (!opLogFile) {
        opLogFile->close();
        delete opLogFile;
        opLogFile = nullptr;
    }

    if (!sysLogFile) {
        sysLogFile->close();
        delete sysLogFile;
        sysLogFile = nullptr;
    }
}

}// namespace qt
}// namespace cdom
}// namespace rrdemo
