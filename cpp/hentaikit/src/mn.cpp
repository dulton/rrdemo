/* ************************************************************************//*!
 * \copyright The MIT License
 ******************************************************************************/

#include <QApplication>
#include <QCommandLineParser>
#include <QSettings>
#include <QTimer>

#include "log.hpp"

#include "ui/mnwd.hpp"

namespace {

/* ****************************************************//*!
 * \brief Command Support
 * \param app The application.
 **********************************************************/
void commandLineSupport(QCoreApplication &app) {
   app.setOrganizationDomain(qApp->translate("app", "orgDomain"));
   app.setOrganizationName(qApp->translate("app", "orgName"));
   app.setApplicationName(qApp->translate("app", "application"));
   app.setApplicationVersion(qApp->translate("app", "version"));

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

   parser.process(app);

   /* Parse */
   if (parser.isSet("v") || parser.isSet("h")) {
      QTimer::singleShot(0, &app, &QCoreApplication::quit);
      return;
   }

   const QStringList args {parser.positionalArguments()};
   if (0 < args.count()) {
      QString arg_1 {args.at(0)};
      QString arg_2 {args.at(1)};
   }

   bool    opt_b {parser.isSet("b")};
   QString opt_s {parser.value("s")};

   /* ... */

   return;
}

/* ****************************************************//*!
 * \brief Settings Support
 * \since 2016-2-14
 **********************************************************/
void settingsSupport(void) {
   QSettings settings("settings.ini", QSettings::Format::IniFormat, qApp);
   settings.setIniCodec("UTF-8");
}

/* ****************************************************//*!
 * \brief Log Support
 **********************************************************/
void logSupport(void) {
   nsp::logInit("log.txt", QtDebugMsg);

   qInstallMessageHandler(nsp::logHandler);

   QObject::connect(qApp, &QApplication::destroyed,
                    &nsp::logDstr);
}

}  // namespace

/* ****************************************************//*!
 * \brief Entry Point
 * \param argc Argument count.
 * \param argv Argument vector.
 * \return Exit status.
 **********************************************************/
int main(int argc, char *argv[]) {
   QApplication app(argc, argv);
   commandLineSupport(app);
   logSupport();

   nsp::MnWd mnwd;
   mnwd.show();

   return app.exec();
}
