/** \file
 *  \sa <http://doc.qt.io/qt-5/qguiapplication.html>
 *  \sa <http://doc.qt.io/qt-5/qqmlapplicationengine.html>
 *  \author zhengrr
 *  \date 2016-11-29 – 12-8
 *  \copyright The MIT License
 */
#include <QGuiApplication>
#include <QQmlApplicationEngine>

namespace {
int altmain(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
#ifdef NDEBUG
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
#else
    engine.load(QUrl(QStringLiteral("qml/main.qml")));
#endif

    return app.exec();
}
}// namespace

#ifndef ENTRY_SWITCH
int main(int argc, char *argv[]) { return altmain(argc, argv); }
#endif// ENTRY SWITC
