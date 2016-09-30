/* ************************************************************************//*!
 * \file
 * \author { list of authors }
 * \date { date description }
 * \copyright { copyright description }
 ******************************************************************************/

#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <QWidget>

namespace nsp {

namespace Ui {
class Wgt;
}  // namespace Ui

/* ****************************************************//*!
 * \brief { brief description }
 * \details { detailed description }
 * \since { text }
 **********************************************************/
class Wgt : public QWidget {
   Q_OBJECT

private:
   explicit Wgt(const Wgt &) = delete;
   explicit Wgt(Wgt &&) = delete;
   Wgt &operator=(const Wgt &) = delete;
   Wgt &operator=(Wgt &&) = delete;

public:
   explicit Wgt(QWidget *parent = nullptr);
   ~Wgt(void);

private:
   Ui::Wgt *ui {nullptr};
};  // class Wgt

}  // namespace nsp

#endif  // WIDGET_HPP
