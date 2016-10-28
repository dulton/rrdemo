/** \copyright The MIT License */

#include "log.hpp"

#include <cassert>

#include <QDateTime>
#include <QFileInfo>
#include <QMutex>
#include <QTextStream>

namespace {

QFile *file {nullptr};
QtMsgType logLevel {QtWarningMsg};

}// namespace

namespace rrdemo {
namespace cpp {
namespace qt {

QtMsgType getLogLevel(void) {
   return logLevel;
}

void setLogLevel(const QtMsgType level) {
   logLevel = level;
}

void logInitialize(const QString &path, const QtMsgType level) {
   static QMutex mutex;
   mutex.lock();

   Q_CHECK_PTR(!file);
   if (file) return;

   file = new QFile(path);
   if (!file->open(QIODevice::WriteOnly | QIODevice::Append))
      Q_ASSERT(false);

   logLevel = level;

   mutex.unlock();
}

void logHandler(QtMsgType type,
                const QMessageLogContext & ctx,
                const QString &msg) {
   Q_CHECK_PTR(file);
   if (!file) return;

   if (type < logLevel) return;

   const QString timeStr {
      QDateTime::currentDateTime().toString("yyMMdd HH:mm:ss.zzz")};

   QString typeStr;
   switch (type) {
   case QtDebugMsg:    typeStr = "[Debug]";    break;
   case QtWarningMsg:  typeStr = "[Warning]";  break;
   case QtCriticalMsg: typeStr = "[Critical]"; break;
   case QtFatalMsg:    typeStr = "[*Fatal*]";  break;
   case QtInfoMsg:     typeStr = "[Info]";     break;
   default:            Q_ASSERT(false);        break;
   }

   QString localStr;
   switch (type) {
   case QtDebugMsg:          break;
   case QtWarningMsg:        break;
   case QtCriticalMsg:       //break;
   case QtFatalMsg:
      localStr = QString(" \t@%1:%2:%3")
         .arg(QFileInfo(ctx.file).fileName())
         .arg(ctx.line)
         .arg(ctx.function);
      break;
   case QtInfoMsg:           break;
   default: Q_ASSERT(false); break;
   }

   const QString message {
      QString("%1 %2 \t%3%4").arg(timeStr, typeStr, msg, localStr)};

   static QMutex mutex;
   mutex.lock();

   QTextStream stream(file);
   stream << message << "\n";
   stream.flush();

   mutex.unlock();
}

void logDestroy(void) {
   static QMutex mutex;
   mutex.lock();

   assert(file);
   if (!file) return;

   file->close();
   delete file;
   file = nullptr;

   mutex.unlock();
}

}// namespace qt
}// namespace cpp
}// namespace rrdemo
