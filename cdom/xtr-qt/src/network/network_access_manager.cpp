/** \file
 *  \sa <http://doc.qt.io/qt-5/qnetworkaccessmanager.html>
 *  \author zhengrr
 *  \date 2016-12-7
 *  \copyright The MIT License
 */
#include <QApplication>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTextBrowser>

namespace {
int altmain(int argc, char *argv[])
{
#error Can't compile
    QApplication app(argc, argv);

    QTextBrowser browser;
    browser.show();

    QNetworkReply *reply {QNetworkAccessManager(&app).get(
        QNetworkRequest(QUrl(
        QStringLiteral("http://info.cern.ch/hypertext/WWW/TheProject.html")
        ))
        )};

    QObject::connect(reply, &QIODevice::readyRead,
                     [=, &browser]() {
        browser.append(reply->readAll());
    });

    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
                     [=](const QNetworkReply::NetworkError /*error*/) {
        qDebug("Network Error: %s", reply->errorString().toUtf8().data());
    });

    QObject::connect(reply, &QNetworkReply::sslErrors,
                     [](const QList<QSslError> &errors) {
        for (const auto error : errors) {
            qDebug("Network SSL Error: %s", error.errorString().toUtf8().data());
        }
    });

    return app.exec();
}
}// namespace

#ifndef ENTRY_SWITCH
int main(int argc, char *argv[]) { return altmain(argc, argv); }
#endif// ENTRY SWITCH
