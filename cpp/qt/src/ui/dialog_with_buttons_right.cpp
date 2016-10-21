/** \copyright The MIT License */

#include "dialog_with_buttons_right.hpp"
#include "ui_dialog_with_buttons_right.h"

namespace rrdemo {
namespace cpp {
namespace qt {

DialogWithButtonsRight::DialogWithButtonsRight(QWidget *parent) :
QDialog(parent), ui {new Ui::DialogWithButtonsRight} {
   ui->setupUi(this);
}

DialogWithButtonsRight::~DialogWithButtonsRight() {
   delete ui;
   ui = nullptr;
}

}// namespace qt
}// namespace cpp
}// namespace rrdemo
