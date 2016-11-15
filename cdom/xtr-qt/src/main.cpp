/** \file
 *  \author zhengrr
 *  \date 2016-2-14 – 11-15
 *  \copyright The MIT License
 */
#include <QApplication>

#include "ui/main_window.hpp"

#ifdef ENTRY_SWITCH
/// Qt程序入口。
/** \param argc 参数计数。
 *  \param argv 参数向量。
 *  \return 退出状态。
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    rrdemo::cdom::qt::MainWindow mwd;
    mwd.show();

    return app.exec();
}
#endif// ENTRY SWITCH
