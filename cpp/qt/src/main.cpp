/** \copyright The MIT License */
#include <QApplication>
#include <QCommandLineParser>
#include <QSettings>
#include <QTimer>

#include "log.hpp"

#include "ui/tab_window_merge_title_bar.hpp"

namespace {

/// 命令行支持
/**
 */
void commandLineSupport() {
   qApp->setOrganizationDomain(qApp->translate("app", "orgDomain"));
   qApp->setOrganizationName(qApp->translate("app", "orgName"));
   qApp->setApplicationName(qApp->translate("app", "application"));
   qApp->setApplicationVersion(qApp->translate("app", "version"));

   /* Command Line */
   QCommandLineParser parser;
   parser.setApplicationDescription(qApp->translate("app", "description"));
   // Argument
   parser.addPositionalArgument("name", qApp->translate("app", "description"));
   // Option
   parser.addVersionOption();
   parser.addHelpOption();
   parser.addOption({{"n", "nAlt"}, qApp->translate("app", "description")});
   parser.addOption({{"m", "mAlt"}, qApp->translate("app", "description"),
                    qApp->translate("app", "valueName")
   });

   parser.process(*qApp);

   /* Parse */
   if (parser.isSet("v") || parser.isSet("h")) {
      QTimer::singleShot(0, qApp, &QCoreApplication::quit);
      return;
   }

   const QStringList args {parser.positionalArguments()};
   if (0 < args.count()) {
      QString arg_1 {args.at(0)};
      QString arg_2 {args.at(1)};
   }

//   bool    opt_b {parser.isSet("b")};
//   QString opt_s {parser.value("s")};

   /* ... */
}

/// 设置支持
/** \since 2016-2-14
 */
void settingsSupport(void) {
   QSettings settings("settings.ini", QSettings::Format::IniFormat, qApp);
   settings.setIniCodec("UTF-8");
}

/// 日志支持
/**
 */
void logSupport(void) {
   using namespace rrdemo::cpp::qt;
   logInitialize("log.txt", QtDebugMsg);
   qInstallMessageHandler(&logHandler);
   QObject::connect(qApp, &QApplication::destroyed, &logDestroy);
}

}// namespace

/// 程序入口
/** \param argc 参数计数
 *  \param argv 参数向量
 *  \return 退出状态
 */
int main(int argc, char *argv[]) {
   QApplication app(argc, argv);
   commandLineSupport();
   logSupport();

   rrdemo::cpp::qt::TabWindowMergeTitleBar tabWindow;
   tabWindow.show();

   return app.exec();
}
