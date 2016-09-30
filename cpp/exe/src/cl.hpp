/* ************************************************************************//*!
 * \file
 * \author { list of authors }
 * \date { date description }
 * \copyright { copyright description }
 ******************************************************************************/

#ifndef CL_HPP
#define CL_HPP

namespace nsp {

/* ****************************************************//*!
 * \brief { brief description }
 * \details { detailed description }
 * \pre { description of the precondition }
 * \post { description of the postcondition }
 * \warning { warning message }
 * \bug { bug description }
 * \since { text }
 **********************************************************/
class Cl {
   explicit Cl(const Cl &) = delete;
   explicit Cl(Cl &&) = delete;
   Cl &operator=(const Cl &) = delete;
   Cl &operator=(Cl &&) = delete;

public:
   explicit Cl(void) = default;
   ~Cl(void) = default;
};  // class Cl

}  // namespace nsp

#endif  // CL_HPP
