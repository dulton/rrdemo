/* ************************************************************************//*!
 * \file
 * \author { list of authors }
 * \date { date description }
 * \copyright { copyright description }
 ******************************************************************************/

#ifndef DLGWOBTNS_HPP
#define DLGWOBTNS_HPP

#include <QDialog>

namespace nsp {

namespace Ui {
class DlgWoBtns;
}  // namespace Ui

/* ****************************************************//*!
 * \brief { brief description }
 * \details { detailed description }
 * \since { text }
 **********************************************************/
class DlgWoBtns : public QDialog {
   Q_OBJECT

private:
   explicit DlgWoBtns(const DlgWoBtns &) = delete;
   explicit DlgWoBtns(DlgWoBtns &&) = delete;
   DlgWoBtns &operator=(const DlgWoBtns &) = delete;
   DlgWoBtns &operator=(DlgWoBtns &&) = delete;

public:
   explicit DlgWoBtns(QWidget *parent = nullptr);
   ~DlgWoBtns(void);

private:
   Ui::DlgWoBtns *ui {nullptr};
};  // class DlgWoBtns

}  // namespace nsp

#endif  // DLGWOBTNS_HPP
