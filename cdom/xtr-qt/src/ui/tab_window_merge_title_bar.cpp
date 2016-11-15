/** \copyright The MIT License */
#include "tab_window_merge_title_bar.hpp"
#include "ui_tab_window_merge_title_bar.h"

#include <QTimer>

namespace rrdemo {
namespace cdom {
namespace qt {

TabWindowMergeTitleBar::TabWindowMergeTitleBar(QWidget *parent) :
QMainWindow(parent), ui {new Ui::TabWindowMergeTitleBar}
{
    ui->setupUi(this);
    initialize();
}

TabWindowMergeTitleBar::~TabWindowMergeTitleBar()
{
    delete ui;  ui = nullptr;
}

void TabWindowMergeTitleBar::on_titleBarMinimizeButton_clicked() const
{
    if (isMinimized()) {
        QTimer::singleShot(0, this, &QWidget::showNormal);
    } else {
        QTimer::singleShot(0, this, &QWidget::showMinimized);
    }
}

void TabWindowMergeTitleBar::on_titleBarMaximizeButton_clicked() const
{
    if (isMaximized()) {
        QTimer::singleShot(0, this, &QWidget::showNormal);
    } else {
        QTimer::singleShot(0, this, &QWidget::showMaximized);
    }
}

void TabWindowMergeTitleBar::on_titleBarCloseButton_clicked() const
{
    QTimer::singleShot(0, this, &QWidget::close);
}

void TabWindowMergeTitleBar::initialize()
{
    setWindowFlags(Qt::CustomizeWindowHint);
}

}// namespace qt
}// namespace cdom
}// namespace rrdemo
