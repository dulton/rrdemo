/**************************************************************************//*!
 * \copyright The MIT License (MIT)
 ******************************************************************************/

#include "singleton.hpp"

namespace nsp {

Singleton *const Singleton::instance {new Singleton};

}  // namespace nsp
