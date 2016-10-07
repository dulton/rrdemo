/* ************************************************************************//*!
 * \file
 * \author { list of authors }
 * \date { date description }
 * \copyright { copyright description }
 ******************************************************************************/

#ifndef CL_HPP
#define CL_HPP

#include <QObject>

namespace nsp {

/* ****************************************************//*!
 * \brief { brief description }
 * \details { detailed description }
 * \since { text }
 **********************************************************/
class Cl : public QObject {
   Q_OBJECT

private:
   explicit Cl(const Cl &) = delete;
   explicit Cl(Cl &&) = delete;
   Cl &operator=(const Cl &) = delete;
   Cl &operator=(Cl &&) = delete;

public:
   explicit Cl(QObject *parent = nullptr);
   ~Cl(void) = default;

};  // class Cl

}  // namespace nsp

#endif  // CL_HPP
