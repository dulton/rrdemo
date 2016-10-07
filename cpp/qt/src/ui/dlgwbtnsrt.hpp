/* ************************************************************************//*!
 * \file
 * \author { list of authors }
 * \date { date description }
 * \copyright { copyright description }
 ******************************************************************************/

#ifndef DLGWBTNSRT_HPP
#define DLGWBTNSRT_HPP

#include <QDialog>

namespace nsp {

namespace Ui {
class DlgWBtnsRt;
}  // namespace Ui

/* ****************************************************//*!
 * \brief { brief description }
 * \details { detailed description }
 * \since { text }
 **********************************************************/
class DlgWBtnsRt : public QDialog {
   Q_OBJECT

private:
   explicit DlgWBtnsRt(const DlgWBtnsRt &) = delete;
   explicit DlgWBtnsRt(DlgWBtnsRt &&) = delete;
   DlgWBtnsRt &operator=(const DlgWBtnsRt &) = delete;
   DlgWBtnsRt &operator=(DlgWBtnsRt &&) = delete;

public:
   explicit DlgWBtnsRt(QWidget *parent = nullptr);
   ~DlgWBtnsRt(void);

private:
   Ui::DlgWBtnsRt *ui {nullptr};
};  // class DlgWBtnsRt

}  // namespace nsp

#endif  // DLGWBTNSRT_HPP
