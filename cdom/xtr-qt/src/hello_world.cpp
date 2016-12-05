/** \file
 *  \author zhengrr
 *  \date 2016-11-30
 *  \copyright The MIT License
 */
#include <QApplication>
#include <QLabel>

namespace {
int altmain1(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QLabel label(QStringLiteral("hello, world"));
    label.show();

    return app.exec();
}
}// namespace
#ifdef ENTRY_SWITCH
int main(int argc, char *argv[]) { return altmain1(argc, argv); }
#endif// ENTRY SWITCH

namespace {
int altmain2(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QLabel *label {new QLabel(QStringLiteral("hello, world"))};
    label->setAttribute(Qt::WA_DeleteOnClose);
    label->show();

    return app.exec();
}
}// namespace
#ifdef ENTRY_SWITCH
int main(int argc, char *argv[]) { return altmain2(argc, argv); }
#endif// ENTRY SWITCH
