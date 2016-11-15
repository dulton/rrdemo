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
        logfile = new QFile("log.txt");
        logfile->open(QIODevice::WriteOnly | QIODevice::Append);
    }

    QString time {QDateTime::currentDateTime().toString("yy-MM-dd HH:mm:ss.zzz")};

    QString typea;
    switch (type) {
    case QtDebugMsg:     typea = "[D]";  break;
    case QtWarningMsg:   typea = "[W]";  break;
    case QtCriticalMsg:  typea = "[C]";  break;
    case QtFatalMsg:     typea = "[F]";  break;
    case QtInfoMsg:      typea = "[I]";  break;
    default: Q_ASSERT(false); abort();
    }

    QString local;
    switch (type) {
    case QtDebugMsg:     break;
    case QtWarningMsg:   break;
    case QtCriticalMsg:  // break through
    case QtFatalMsg:
        local = QString(" @%1:%2: %3")
            .arg(QFileInfo(context.file).fileName())
            .arg(context.line)
            .arg(context.function);
        break;
    case QtInfoMsg:      break;
    default: Q_ASSERT(false); abort();
    }

    static QMutex mutex;
    mutex.lock();
    QTextStream stream(logfile);
    stream << QString("%1 %2 %3%4").arg(time, typea, message, local) << "\r\n";
    stream.flush();
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
