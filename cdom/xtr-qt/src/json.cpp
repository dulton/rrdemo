/** \file
 *  \sa <http://doc.qt.io/qt-5/qjsondocument.html>
 *  \author zhengrr
 *  \date 2016-11-28
 *  \copyright The MIT License
 */
#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#ifdef ENTRY_SWITCH
/// 写 JSON 文件。
/**
 *
 */
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QFile jsonFile(QStringLiteral("json.dat"));
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open json (data) file.");
        return false;
    }

    QJsonObject jsonObject;
    jsonObject["lvl1"] = QStringLiteral("33");

    QJsonDocument jsonDoc(jsonObject);
    jsonFile.write(jsonDoc.toBinaryData());

    return app.exec();
}
#endif// ENTRY SWITCH

#ifdef ENTRY_SWITCH
/// 读 JSON 文件。
/**
 *
 */
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QFile jsonFile(QStringLiteral("json.dat"));
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open json (data) file.");
        return false;
    }
    QByteArray jsonData {jsonFile.readAll()};
    QJsonDocument jsonDoc {QJsonDocument::fromBinaryData(jsonData)};

    return app.exec();
}
#endif// ENTRY SWITCH
