/** \file
 *  \author zhengrr
 *  \date 2016-11-15
 *  \copyright The MIT License
 */
#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDebug>

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCryptographicHash md4parser(QCryptographicHash::Md4);
    QCryptographicHash md5parser(QCryptographicHash::Md5);
    QCryptographicHash sha1parser(QCryptographicHash::Sha1);
    QCryptographicHash sha224parser(QCryptographicHash::Sha224);
    QCryptographicHash sha256parser(QCryptographicHash::Sha256);
    QCryptographicHash sha384parser(QCryptographicHash::Sha384);
    QCryptographicHash sha512parser(QCryptographicHash::Sha512);
    QCryptographicHash sha3224parser(QCryptographicHash::Sha3_224);
    QCryptographicHash sha3256parser(QCryptographicHash::Sha3_256);
    QCryptographicHash sha3384parser(QCryptographicHash::Sha3_384);
    QCryptographicHash sha3512parser(QCryptographicHash::Sha3_512);

    QByteArray data;
    if (1 < argc)
        data = QByteArray(argv[1]);
    else
        data = QByteArray("1337");
    md4parser.addData(data);
    md5parser.addData(data);
    sha1parser.addData(data);
    sha224parser.addData(data);
    sha256parser.addData(data);
    sha384parser.addData(data);
    sha512parser.addData(data);
    sha3224parser.addData(data);
    sha3256parser.addData(data);
    sha3384parser.addData(data);
    sha3512parser.addData(data);

    qInfo() << "Input:" << data;
    qInfo() << "MD4:" << md4parser.result().toHex().toUpper();
    qInfo() << "MD5:" << md5parser.result().toHex().toUpper();
    qInfo() << "SHA1:" << sha1parser.result().toHex().toUpper();
    qInfo() << "SHA2-224:" << sha224parser.result().toHex().toUpper();
    qInfo() << "SHA2-256:" << sha256parser.result().toHex().toUpper();
    qInfo() << "SHA2-384:" << sha384parser.result().toHex().toUpper();
    qInfo() << "SHA2-512:" << sha512parser.result().toHex().toUpper();
    qInfo() << "SHA3-224:" << sha3224parser.result().toHex().toUpper();
    qInfo() << "SHA3-256:" << sha3256parser.result().toHex().toUpper();
    qInfo() << "SHA3-384:" << sha3384parser.result().toHex().toUpper();
    qInfo() << "SHA3-512:" << sha3512parser.result().toHex().toUpper();

    return app.exec();
}
#endif// ENTRY SWITCH
