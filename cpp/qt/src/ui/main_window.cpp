/** \copyright The MIT License */
#include "main_window.hpp"
#include "ui_main_window.h"

namespace rrdemo {
namespace cpp {
namespace qt {

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent), ui {new Ui::MainWindow} {
   ui->setupUi(this);
}

MainWindow::~MainWindow() {
   delete ui;
   ui = nullptr;
}

}// namespace qt
}// namespace cpp
}// namespace rrdemo
