/* ************************************************************************//*!
 * \copyright { copyright description }
 ******************************************************************************/

#include "mnwd.hpp"
#include "ui_mnwd.h"

namespace nsp {

MnWd::MnWd(QWidget *parent) :
QMainWindow(parent), ui {new Ui::MnWd} {
   ui->setupUi(this);
}

MnWd::~MnWd(void) {
   delete ui;
   ui = nullptr;
}

}  // namespace nsp
