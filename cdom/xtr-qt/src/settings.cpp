/** \file
 *  \sa <http://doc.qt.io/qt-5/qsettings.html>
 *  \author zhengrr
 *  \date 2016-2-14 – 11-15
 *  \copyright The MIT License
 */
#include <QCoreApplication>
#include <QSettings>

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QSettings settings("settings.ini", QSettings::IniFormat, &app);
    settings.setIniCodec("UTF-8");
    settings.sync();
    settings.setValue("category/item",
                      settings.value("category/item", 0).toInt() + 1);
    settings.sync();

    return app.exec();
}
#endif// ENTRY SWITCH
