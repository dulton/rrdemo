/** \copyright The MIT License */
#include "dialog_with_buttons_bottom.hpp"
#include "ui_dialog_with_buttons_bottom.h"

namespace rrdemo {
namespace cdom {
namespace qt {

DialogWithButtonsBottom::DialogWithButtonsBottom(QWidget *parent) :
QDialog(parent), ui {new Ui::DialogWithButtonsBottom}
{
    ui->setupUi(this);
}

DialogWithButtonsBottom::~DialogWithButtonsBottom()
{
    delete ui;  ui = nullptr;
}

}// namespace qt
}// namespace cdom
}// namespace rrdemo
