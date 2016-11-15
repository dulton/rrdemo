/** \copyright The MIT License */
#include "widget.hpp"
#include "ui_widget.h"

namespace rrdemo {
namespace cdom {
namespace qt {

Widget::Widget(QWidget *parent) :
QWidget(parent), ui {new Ui::Widget}
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;  ui = nullptr;
}

}// namespace qt
}// namespace cdom
}// namespace rrdemo
