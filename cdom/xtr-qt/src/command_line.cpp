/** \file
 *  \brief 命令行支持。
 *  \author zhengrr
 *  \date 2016-2-14 – 11-15
 *  \copyright The MIT License
 */
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setOrganizationDomain(app.translate("app", "Organization domain."));
    app.setOrganizationName(app.translate("app", "Organization name."));
    app.setApplicationName(app.translate("app", "Application name."));
    app.setApplicationVersion(app.translate("app", "Application version."));

    QCommandLineParser parser;
    parser.setApplicationDescription(app.translate("app", "Application description."));
    /* Arguments */
    Q_CONSTEXPR int argsc {1};
    parser.addPositionalArgument(QStringLiteral("arg"), app.translate("app", "Argument."));
    /* Options */
    parser.addHelpOption();     // <http://doc.qt.io/qt-5/qcommandlineparser.html#addHelpOption>
    parser.addVersionOption();  // <http://doc.qt.io/qt-5/qcommandlineparser.html#addVersionOption>
    parser.addOptions({
        {
            {QStringLiteral("b"), QStringLiteral("optboolean")},
            app.translate("app", "Option boolean.")
        },
        {
            {QStringLiteral("s"), QStringLiteral("optstring")},
            app.translate("app", "Option string."),
            app.translate("app", "string")
        }
    });

    parser.process(app);  // Parsing

    /* Parse help & version options */
    if (parser.isSet(QStringLiteral("h")) || parser.isSet(QStringLiteral("v")))
        return EXIT_SUCCESS;

    /* Parse arguments */
    if (parser.positionalArguments().count() < argsc) {
        qWarning("Missing command-line arguments.");
        return EXIT_FAILURE;
    } else if (argsc < parser.positionalArguments().count()) {
        qWarning("Too many command-line arguments.");
        return EXIT_FAILURE;
    }
    const QString argName {parser.positionalArguments().at(0)};

    /* Parse options */
    const bool optM {parser.isSet(QStringLiteral("m"))};
    QString optN {parser.value(QStringLiteral("n"))};

    qInfo() << "argName: " << argName;
    qInfo() << "optM: " << optM;
    qInfo() << "optN: " << optN;

    return 0;
}
#endif// ENTRY SWITCH
