/* ************************************************************************//*!
 * \file
 * \author zhengrr
 * \date 2016-8-3
 * \copyright The MIT License
 ******************************************************************************/

#ifndef LANGCPP__SRC_HPP
#define LANGCPP__SRC_HPP

#if defined _WIN32 || defined __CYGWIN__
#   define LANGCPP_EXPORT __declspec(dllexport)
#   define LANGCPP_IMPORT __declspec(dllimport)
#   define LANGCPP_LOCAL
#elif __GNUC__ >= 4
#   define LANGCPP_EXPORT __attribute__((visibility("default")))
#   define LANGCPP_IMPORT __attribute__((visibility("default")))
#   define LANGCPP_LOCAL  __attribute__((visibility("hidden")))
#else
#   define LANGCPP_IMPORT
#   define LANGCPP_EXPORT
#   define LANGCPP_LOCAL
#endif

#ifdef LANGCPP_EXPORTS
#   define LANGCPP_API LANGCPP_EXPORT
#else
#   define LANGCPP_API LANGCPP_IMPORT
#endif

namespace langcpp {

/* ****************************************************//*!
 * \since { text }
 **********************************************************/
LANGCPP_API int Fcn(const int param);

}  // namespace langcpp

#endif  // LANGCPP__SRC_HPP
