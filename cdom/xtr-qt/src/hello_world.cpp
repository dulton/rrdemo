/** \file
 *  \author zhengrr
 *  \date 2016-11-30
 *  \copyright The MIT License
 */
#include <QApplication>
#include <QLabel>

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QLabel label("hello, world");
    label.show();

    return app.exec();
}
#endif// ENTRY SWITCH

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QLabel *label {new QLabel("hello, world")};
    label->setAttribute(Qt::WA_DeleteOnClose);
    label->show();

    return app.exec();
}
#endif// ENTRY SWITCH
