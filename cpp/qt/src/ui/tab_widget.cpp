/** \copyright The MIT License */
#include "tab_widget.hpp"
#include "ui_tab_widget.h"

namespace rrdemo {
namespace cpp {
namespace qt {

TabWidget::TabWidget(QWidget *parent) :
QTabWidget(parent), ui(new Ui::TabWidget) {
   ui->setupUi(this);
}

TabWidget::~TabWidget() {
   delete ui;
   ui = nullptr;
}

}// namespace qt
}// namespace cpp
}// namespace rrdemo
