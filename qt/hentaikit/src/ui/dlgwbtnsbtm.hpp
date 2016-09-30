/* ************************************************************************//*!
 * \file
 * \author { list of authors }
 * \date { date description }
 * \copyright { copyright description }
 ******************************************************************************/

#ifndef DLGWBTNSBTM_HPP
#define DLGWBTNSBTM_HPP

#include <QDialog>

namespace nsp {

namespace Ui {
class DlgWBtnsBtm;
}  // namespace Ui

/* ****************************************************//*!
 * \brief { brief description }
 * \details { detailed description }
 * \since { text }
 **********************************************************/
class DlgWBtnsBtm : public QDialog {
   Q_OBJECT

private:
   explicit DlgWBtnsBtm(const DlgWBtnsBtm &) = delete;
   explicit DlgWBtnsBtm(DlgWBtnsBtm &&) = delete;
   DlgWBtnsBtm &operator=(const DlgWBtnsBtm &) = delete;
   DlgWBtnsBtm &operator=(DlgWBtnsBtm &&) = delete;

public:
   explicit DlgWBtnsBtm(QWidget *parent = nullptr);
   ~DlgWBtnsBtm(void);

private:
   Ui::DlgWBtnsBtm *ui {nullptr};
};  // class DlgWBtnsBtm

}  // namespace nsp

#endif  // DLGWBTNSBTM_HPP
