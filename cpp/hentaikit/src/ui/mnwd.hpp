/* ************************************************************************//*!
 * \file
 * \author { list of authors }
 * \date { date description }
 * \copyright { copyright description }
 ******************************************************************************/

#ifndef MNWD_HPP
#define MNWD_HPP

#include <QMainWindow>

namespace nsp {

namespace Ui {
class MnWd;
}  // namespace Ui

/* ****************************************************//*!
 * \brief { brief description }
 * \details { detailed description }
 * \since { text }
 **********************************************************/
class MnWd : public QMainWindow {
   Q_OBJECT

private:
   explicit MnWd(const MnWd &) = delete;
   explicit MnWd(MnWd &&) = delete;
   MnWd &operator=(const MnWd &) = delete;
   MnWd &operator=(MnWd &&) = delete;

public:
   explicit MnWd(QWidget *parent = nullptr);
   ~MnWd(void);

private:
   Ui::MnWd *ui {nullptr};
};  // class MnWd

}  // namespace nsp

#endif  // MNWD_HPP
