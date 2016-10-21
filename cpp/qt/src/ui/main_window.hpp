/** \file
 *  \author zhengrr
 *  \date 2016-10-20
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCPPQT_MAINWINDOW_HPP
#define _RRDEMOCPPQT_MAINWINDOW_HPP

#include <QMainWindow>

namespace rrdemo {
namespace cpp {
namespace qt {

namespace Ui {
class MainWindow;
}

/// 主界面
/**
 */
class MainWindow : public QMainWindow {
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);
   explicit MainWindow(const MainWindow &) = delete;
   explicit MainWindow(MainWindow &&) = delete;
   MainWindow &operator=(const MainWindow &) = delete;
   MainWindow &operator=(MainWindow &&) = delete;
   ~MainWindow();

private:
   Ui::MainWindow *ui {nullptr};
};// class MainWindow

}// namespace qt
}// namespace cpp
}// namespace rrdemo

#endif// _RRDEMOCPPQT_MAINWINDOW_HPP
