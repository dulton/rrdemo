/** \file
 *  \sa <http://doc.qt.io/qt-5/qdesktopservices.html>
 *  \author zhengrr
 *  \date 2016-11-15 – 28
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
