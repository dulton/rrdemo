/* ************************************************************************//*!
 * \copyright  { copyright description }
 ******************************************************************************/

#include "dlgwbtnsbtm.hpp"
#include "ui_dlgwbtnsbtm.h"

namespace nsp {

DlgWBtnsBtm::DlgWBtnsBtm(QWidget *parent) :
QDialog(parent), ui {new Ui::DlgWBtnsBtm} {
   ui->setupUi(this);
}

DlgWBtnsBtm::~DlgWBtnsBtm(void) {
   delete ui;
   ui = nullptr;
}

}  // namespace nsp
