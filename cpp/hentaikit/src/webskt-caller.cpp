/* ************************************************************************//*!
 * \copyright The MIT License
 ******************************************************************************/

#include <cassert>

#include <QWebSocket>

namespace {

static QWebSocket *webskt {nullptr};

void prep(void) {
   assert(!webskt);
   if (webskt) return;

   webskt = new QWebSocket;

   /* on webskt connected */
   QObject::connect(webskt, &QWebSocket::connected,
                    [](void) {
      /* ... */
   });

   /* on webskt disconnected */
   QObject::connect(webskt, &QWebSocket::disconnected,
                    [](void) {
      /* ... */
   });

   /* on webskt error */
   QObject::connect(webskt, static_cast
                    <void (QWebSocket::*)(QAbstractSocket::SocketError)>
                    (&QWebSocket::error),
                    [](const QAbstractSocket::SocketError error) {
      /* ... */
   });

   /* on webskt textMessageReceived */
   QObject::connect(webskt, &QWebSocket::textMessageReceived,
                    [](const QString &message) {
      /* ... */
   });
};

void open(const QUrl &url) {
   assert(webskt);
   if (!webskt) return;

   webskt->open(url);
}

void close(const QWebSocketProtocol::CloseCode code, const QString &reason) {
   assert(webskt);
   if (!webskt) return;

   webskt->close(code, reason);
}

}  // namespace
