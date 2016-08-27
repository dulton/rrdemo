/* ************************************************************************//*!
 * \copyright { copyright description }
 ******************************************************************************/

#include "dlgwbtnsrt.hpp"
#include "ui_dlgwbtnsrt.h"

namespace nsp {

DlgWBtnsRt::DlgWBtnsRt(QWidget *parent) :
QDialog(parent), ui {new Ui::DlgWBtnsRt} {
   ui->setupUi(this);
}

DlgWBtnsRt::~DlgWBtnsRt(void) {
   delete ui;
   ui = nullptr;
}

}  // namespace nsp
