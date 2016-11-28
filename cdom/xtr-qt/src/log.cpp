/** \file
 *  \brief 日志支持。
 *  \sa <http://doc.qt.io/qt-5/qtglobal.html#qInstallMessageHandler>
 *  \author zhengrr
 *  \date 2016-1-9 – 11-15
 *  \copyright The MIT License
 */
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMutex>
#include <QString>
#include <QTextStream>

namespace {
void MessageHandler(QtMsgType type,
                    const QMessageLogContext &context,
                    const QString &message)
{
    static QFile *logfile {nullptr};
    if (!logfile) {
        static QMutex mutex;
        mutex.lock();
        if (!logfile) {
            logfile = new QFile(QStringLiteral("log.txt"));
            logfile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
        }
        mutex.unlock();
    }

    QString logtext;

    // time
    logtext += QDateTime::currentDateTime().toString(QStringLiteral("yy-MM-dd HH:mm:ss.zzz"));

    // type
    switch (type) {
    case QtDebugMsg:     logtext += QStringLiteral(" [D]");  break;
    case QtWarningMsg:   logtext += QStringLiteral(" [W]");  break;
    case QtCriticalMsg:  logtext += QStringLiteral(" [C]");  break;
    case QtFatalMsg:     logtext += QStringLiteral(" [F]");  break;
    case QtInfoMsg:      logtext += QStringLiteral(" [I]");  break;
    default: Q_ASSERT(false);
    }

    // message
    logtext += QString(" %1").arg(message);

    // local
    switch (type) {
    case QtDebugMsg:     break;
    case QtWarningMsg:   break;
    case QtCriticalMsg:  // break through
    case QtFatalMsg:
        logtext += QString(" @%1:%2: %3")
            .arg(QFileInfo(context.file).fileName())
            .arg(context.line)
            .arg(context.function);
        break;
    case QtInfoMsg:      break;
    default: Q_ASSERT(false);
    }

    static QMutex mutex;
    mutex.lock();
    QTextStream stream(logfile);
    stream << logtext << endl;
    mutex.unlock();
}
}// namespace

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    qInstallMessageHandler(MessageHandler);

    qDebug("Debug message.");
    qWarning("Warning message.");
    qInfo("Info message.");
    qCritical("Critical message.");
    qFatal("Fatal message.");

    return app.exec();
}
#endif// ENTRY SWITCH
