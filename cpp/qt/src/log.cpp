/* ************************************************************************//*!
 * \copyright The MIT License
 ******************************************************************************/

#include "log.hpp"

#include <cassert>

#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

namespace {

static QFile *file {nullptr};
static QtMsgType logLevel {QtWarningMsg};

}  // namespace

namespace nsp {

const QtMsgType getLogLevel(void) {
   return logLevel;
}

void setLogLevel(const QtMsgType level) {
   logLevel = level;
}

void logInit(const QString &path, const QtMsgType level) {
   static QMutex mutex;
   mutex.lock();

   assert(!file);
   if (file) return;

   file = new QFile(path);
   if (!file->open(QIODevice::WriteOnly | QIODevice::Append))
      assert(false);

   setLogLevel(level);

   mutex.unlock();
}

void logHandler(QtMsgType type,
                const QMessageLogContext &context,
                const QString &msg) {
   assert(file);
   if (!file) return;

   if (type < getLogLevel()) return;

   const QString datetime {
      QDateTime::currentDateTime().toString("yyMMdd HH:mm:ss.zzz")};

   QString typ;
   switch (type) {
      case QtDebugMsg:    typ = "[Debug]";    break;
      case QtWarningMsg:  typ = "[Warning]";  break;
      case QtCriticalMsg: typ = "[Critical]"; break;
      case QtFatalMsg:    typ = "[*Fatal*]";  break;
      case QtInfoMsg:     typ = "[Info]";     break;
   }

   QString loc;
   switch (type) {
      case QtDebugMsg: break;
      case QtWarningMsg: break;
      case QtCriticalMsg: /*break;*/
      case QtFatalMsg:
         loc = QString(" \t@%1:%2:%3")
            .arg(QFileInfo(context.file).fileName())
            .arg(context.line)
            .arg(context.function);
         break;
      case QtInfoMsg: break;
   }

   const QString message {
      QString("%1 %2 \t%3%4").arg(datetime, typ, msg, loc)};

   static QMutex mutex;
   mutex.lock();

   QTextStream stream(file);
   stream << message << "\n";
   stream.flush();

   mutex.unlock();
}

void logDstr(void) {
   static QMutex mutex;
   mutex.lock();

   assert(file);
   if (!file) return;

   file->close();
   delete file;
   file = nullptr;

   mutex.unlock();
}

}  // namespace nsp
