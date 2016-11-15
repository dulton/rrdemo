/** \copyright The MIT License */
#include "dialog_without_buttons.hpp"
#include "ui_dialog_without_buttons.h"

namespace rrdemo {
namespace cdom {
namespace qt {

DialogWithoutButtons::DialogWithoutButtons(QWidget *parent) :
QDialog(parent), ui {new Ui::DialogWithoutButtons}
{
    ui->setupUi(this);
}

DialogWithoutButtons::~DialogWithoutButtons()
{
    delete ui;  ui = nullptr;
}

}// namespace qt
}// namespace cdom
}// namespace rrdemo
