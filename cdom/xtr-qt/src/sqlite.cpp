/** \file
 *  \sa <http://doc.qt.io/qt-5/sql-driver.html>
 *  \sa <http://doc.qt.io/qt-5/qsqldatabase.html>
 *  \sa <http://doc.qt.io/qt-5/qsqlquery.html>
 *  \sa <http://stackoverflow.com/questions/2319280>
 *  \author zhengrr
 *  \date 2016-11-16
 *  \copyright The MIT License
 */
#include <QCoreApplication>
#include <QDebug>
#include <QSqlQuery>

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sqlite.db");
    if (!db.open()) {
        qFatal("Database open faild.");
    }

    QSqlQuery query("SELECT * FROM table;");
    query.exec();
    while (query.next()) {
        qInfo() << query.value(0).toString();
    }

    return app.exec();
}
#endif// ENTRY SWITCH
