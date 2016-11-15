/** \file
 *  \sa <http://doc.qt.io/qt-5/qabstractsocket.html>
 *  \sa <http://doc.qt.io/qt-5/qwebsocket.html>
 *  \author zhengrr
 *  \date 2016-11-15
 *  \copyright The MIT License
 */
#include <QCoreApplication>
#include <QWebSocket>

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QWebSocket *webskt {new QWebSocket};

    QObject::connect(webskt, &QWebSocket::connected, [](void) {
        qInfo("Connected.");
    });

    QObject::connect(webskt, &QWebSocket::disconnected, [](void) {
        qInfo("Disconnected.");
    });

    QObject::connect(webskt, static_cast<void (QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
                     [&webskt](const QAbstractSocket::SocketError error) {
        qInfo() << "Error " << error << ": " << webskt->errorString();
    });

    QObject::connect(webskt, &QWebSocket::textMessageReceived,
                     [](const QString &message) {
        qInfo() << "Data: " << message;
    });

    webskt->open(QUrl("ws://192.168.1.12/ws"));
    //webskt->close(code, reason);

    return app.exec();
}
#endif// ENTRY SWITCH
