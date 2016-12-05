/** \file
 *  \sa <http://doc.qt.io/qt-5/qabstractsocket.html>
 *  \sa <http://doc.qt.io/qt-5/qwebsocket.html>
 *  \author zhengrr
 *  \date 2016-11-15
 *  \copyright The MIT License
 */
#include <QCoreApplication>
#include <QWebSocket>

namespace {
int altmain(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QWebSocket *webskt {new QWebSocket};

    QObject::connect(webskt, &QWebSocket::connected, [](void) {
        qInfo("WebSocket Connected.");
    });

    QObject::connect(webskt, &QWebSocket::disconnected, [](void) {
        qInfo("WebSocket Disconnected.");
    });

    QObject::connect(webskt, static_cast<void (QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
                     [=](const QAbstractSocket::SocketError /*error*/) {
        qInfo("WebSocket Error %d: %s", webskt->error(), webskt->errorString().toUtf8().data());
    });

    QObject::connect(webskt, &QWebSocket::textMessageReceived,
                     [](const QString &message) {
        qInfo("WebSocket Data: %s", message.toUtf8().data());
    });

    webskt->open(QUrl("ws://192.168.1.12/ws"));

    //webskt->close(code, reason);

    return app.exec();
}
}// namespace

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[]) { return altmain(argc, argv); }
#endif// ENTRY SWITC
