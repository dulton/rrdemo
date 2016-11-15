/** \file
 *  \author zhengrr
 *  \date 2016-11-15
 *  \copyright The MIT License
 */
#include <QApplication>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qInfo() << "Result:" << QDesktopServices::openUrl(QUrl("http://bing.com/"));
    return app.exec();
}
#endif// ENTRY SWITCH
