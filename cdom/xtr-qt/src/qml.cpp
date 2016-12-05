/** \file
 *  \author zhengrr
 *  \date 2016-11-29
 *  \copyright The MIT License
 */
#include <QApplication>
#include <QQuickView>
#include <QQmlContext>

namespace {
int altmain(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQuickView view;
    QQmlContext *context {view.rootContext()};
    context->setContextProperty(QStringLiteral("backgroundColor"), QColor(Qt::yellow));

    view.setSource(QUrl(QStringLiteral("qrc:/qml/main")));
    view.show();

    return app.exec();
}
}// namespace

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[]) { return altmain(argc, argv); }
#endif// ENTRY SWITC
