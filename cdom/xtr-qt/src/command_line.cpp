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

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    /* Arguments */
    const int argsc {1};
    parser.addPositionalArgument("arg", app.translate("app", "Argument."));
    /* Options */
    parser.addOptions({
        {
            {"b", "optboolean"},
        },
        {
            {"s", "optstring"},
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
