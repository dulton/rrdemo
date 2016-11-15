/** \file
 *  \brief 命令行支持。
 *  \author zhengrr
 *  \date 2016-2-14 – 11-15
 *  \copyright The MIT License
 */
#include <iostream>

#include <QCommandLineParser>
#include <QCoreApplication>
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
    const int argsc {1};
    parser.addPositionalArgument("arg", app.translate("app", "Argument."));
    /* Options */
    parser.addHelpOption();     // <http://doc.qt.io/qt-5/qcommandlineparser.html#addHelpOption>
    parser.addVersionOption();  // <http://doc.qt.io/qt-5/qcommandlineparser.html#addVersionOption>
    parser.addOptions({
        {
            {"b", "optboolean"},
            app.translate("app", "Option boolean.")
        },
        {
            {"s", "optstring"},
            app.translate("app", "Option string."),
            app.translate("app", "string")
        }
    });

    parser.process(app);  // Parsing

    /* Parse Arguments */
    if (parser.isSet("v") || parser.isSet("h"))
        return EXIT_SUCCESS;
    if (parser.positionalArguments().count() < argsc)
        return EXIT_FAILURE;  //TODO: missing parameters.
    if (argsc < parser.positionalArguments().count())
        ;  //TODO: too many arguments.
    const QString argName {parser.positionalArguments().at(0)};
    /* Parse Options */
    const bool optM {parser.isSet("m")};
    QString optN {parser.value("n")};

    std::cout << "argName: " << argName.toStdString() << std::endl;
    std::cout << "optM: " << optM << std::endl;
    std::cout << "optN: " << optN.toStdString() << std::endl;

    system("pause");
    return 0;
}
#endif// ENTRY SWITCH
