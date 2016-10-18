/**
 * \copyright The MIT License
 */

#include "dznp-singleton.hpp"

namespace rrdemo {
namespace cpp {
namespace lang {

Singleton *const Singleton::instance {new Singleton};

}// namespace lang
}// namespace cpp
}// namespace rrdemo
