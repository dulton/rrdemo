/** \file
 *  \author zhengrr
 *  \date 2016-10-21 – 11-15
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMQT_TABWINDOWMERGETITLEBAR_HPP
#define _RRDEMOCDOMQT_TABWINDOWMERGETITLEBAR_HPP

#include <QMainWindow>

namespace rrdemo {
namespace cdom {
namespace qt {

namespace Ui {
class TabWindowMergeTitleBar;
}

/// 合并标题栏的标签窗口。
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
    void on_titleBarMinimizeButton_clicked() const;
    /// 标题栏最大化按钮
    void on_titleBarMaximizeButton_clicked() const;
    /// 标题栏关闭按钮
    void on_titleBarCloseButton_clicked() const;

private:
    void initialize();

    Ui::TabWindowMergeTitleBar *ui {nullptr};
};// class TabWindowMergeTitleBar

}// namespace qt
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMQT_TABWINDOWMERGETITLEBAR_HPP
