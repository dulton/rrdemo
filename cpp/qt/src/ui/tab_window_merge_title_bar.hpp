/** \file
 *  \author zhengrr
 *  \date 2016-10-21
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCPPQT_TABWINDOWMERGETITLEBAR_HPP
#define _RRDEMOCPPQT_TABWINDOWMERGETITLEBAR_HPP

#include <QMainWindow>

namespace rrdemo {
namespace cpp {
namespace qt {

namespace Ui {
class TabWindowMergeTitleBar;
}

/// 合并标题栏的标签窗口
/**
 */
class TabWindowMergeTitleBar : public QMainWindow {
   Q_OBJECT

public:
   explicit TabWindowMergeTitleBar(QWidget *parent = nullptr);
   explicit TabWindowMergeTitleBar(const TabWindowMergeTitleBar &) = delete;
   explicit TabWindowMergeTitleBar(TabWindowMergeTitleBar &&) = delete;
   TabWindowMergeTitleBar &operator=(const TabWindowMergeTitleBar &) = delete;
   TabWindowMergeTitleBar &operator=(TabWindowMergeTitleBar &&) = delete;
   ~TabWindowMergeTitleBar();

private slots:
   /// 标题栏最小化按钮
   void on_titleBarMinimizeButton_clicked();
   /// 标题栏最大化按钮
   void on_titleBarMaximizeButton_clicked();
   /// 标题栏关闭按钮
   void on_titleBarCloseButton_clicked();

private:
   void initialize();

   Ui::TabWindowMergeTitleBar *ui {nullptr};
};// class TabWindowMergeTitleBar

}// namespace qt
}// namespace cpp
}// namespace rrdemo

#endif// _RRDEMOCPPQT_TABWINDOWMERGETITLEBAR_HPP
