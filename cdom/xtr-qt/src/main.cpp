/** \copyright The MIT License */
#include <QApplication>
#include <QCommandLineParser>
#include <QSettings>
#include <QTimer>

#include "log.hpp"

#include "ui/tab_window_merge_title_bar.hpp"

namespace
{

/// 命令行支持.
void CommandLineSupport(const QCoreApplication &app)
{
    app.setOrganizationDomain(app.translate("app", "orgDomain"));
    app.setOrganizationName(app.translate("app", "orgName"));
    app.setApplicationName(app.translate("app", "application"));
    app.setApplicationVersion(app.translate("app", "version"));

    QCommandLineParser parser;
    parser.setApplicationDescription(app.translate("app", "description"));
    // Argument
    parser.addPositionalArgument("name", app.translate("app", "description"));
    // Option
    parser.addVersionOption();
    parser.addHelpOption();
    parser.addOption({{"n", "nAlt"}, app.translate("app", "description")});
    parser.addOption({{"m", "mAlt"}, app.translate("app", "description"),
                      app.translate("app", "valueName")
                     });

    parser.process(app);

    /* Parse */
    if (parser.isSet("v") || parser.isSet("h")) {
        QTimer::singleShot(0, &app, &QCoreApplication::quit);
        return;
    }

    const QStringList args{parser.positionalArguments()};
    if (0 < args.count()) {
        QString arg_1{args.at(0)};
        QString arg_2{args.at(1)};
    }

    bool opt_b{parser.isSet("b")};
    QString opt_s{parser.value("s")};
}

/// 设置支持.
/** \since 2016-2-14
 */
void settingsSupport(void)
{
    QSettings settings("settings.ini", QSettings::Format::IniFormat, qApp);
    settings.setIniCodec("UTF-8");
}

}// namespace

/// 程序入口
/** \param argc 参数计数
 *  \param argv 参数向量
 *  \return 退出状态
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // log
    rrdemo::cdom::qt::LoggingController::Initialize("log.txt");

    CommandLineSupport(app);

    rrdemo::cpp::qt::TabWindowMergeTitleBar tabWindow;
    tabWindow.show();

    return app.exec();
}
