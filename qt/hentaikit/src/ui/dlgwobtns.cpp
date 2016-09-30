/* ************************************************************************//*!
 * \copyright { copyright description }
 ******************************************************************************/

#include "dlgwobtns.hpp"
#include "ui_dlgwobtns.h"

namespace nsp {

DlgWoBtns::DlgWoBtns(QWidget *parent) :
QDialog(parent), ui {new Ui::DlgWoBtns} {
   ui->setupUi(this);
}

DlgWoBtns::~DlgWoBtns(void) {
   delete ui;
   ui = nullptr;
}

}  // namespace nsp
