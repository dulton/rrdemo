/* ************************************************************************//*!
 * \copyright { copyright description }
 ******************************************************************************/

#include "wgt.hpp"
#include "ui_wgt.h"

namespace nsp {

Wgt::Wgt(QWidget *parent) :
QWidget(parent), ui {new Ui::Wgt} {
   ui->setupUi(this);
}

Wgt::~Wgt(void) {
   delete ui;
   ui = nullptr;
}

}  // namespace nsp
