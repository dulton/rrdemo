/** \file
 *  \sa <http://doc.qt.io/qt-5/qdesktopservices.html>
 *  \author zhengrr
 *  \date 2016-11-15 – 12-5
 *  \copyright The MIT License
 */
#include <QApplication>
#include <QDesktopServices>
#include <QTimer>
#include <QUrl>

namespace {
int altmain(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QDesktopServices::openUrl(QUrl("http://qt.io/"));
    QTimer::singleShot(0, &app, &QCoreApplication::quit);
    return app.exec();
}
}// namespace

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[]) { return altmain(argc, argv); }
#endif// ENTRY SWITCH
