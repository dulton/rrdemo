/** \file
 *  \sa <http://doc.qt.io/qt-5/sql-driver.html>
 *  \sa <http://doc.qt.io/qt-5/qsqldatabase.html>
 *  \sa <http://doc.qt.io/qt-5/qsqlquery.html>
 *  \sa <http://stackoverflow.com/questions/2319280>
 *  \author zhengrr
 *  \date 2016-11-16 – 12-5
 *  \copyright The MIT License
 */
#include <QCoreApplication>
#include <QSqlQuery>
#include <QVariant>

namespace {
int altmain(int, char *[])
{
    //QCoreApplication app(argc, argv);

    QSqlDatabase db {QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"))};
    db.setDatabaseName(QStringLiteral("db.sqlite"));
    if (!db.open()) {
        qWarning("Couldn't open database.");
        return -1;
    }

    QSqlQuery query(QStringLiteral("SELECT * FROM 'table';"));
    query.exec();
    
    while (query.next()) {
        qInfo("%s", query.value(0).toString().toUtf8().data());
    }
    return EXIT_SUCCESS;
    //return app.exec();
}
}// namespace

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[]) { return altmain(argc, argv); }
#endif// ENTRY SWITC
