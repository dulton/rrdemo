/** \file
 *  \author zhengrr
 *  \date 2016-8-1 – 10-20
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCLIB_DEF_H
#define _RRDEMOCLIB_DEF_H

#ifdef _MSC_VER
# define RRDEMOCLIB_EXPORT __declspec(dllexport)
# define RRDEMOCLIB_IMPORT __declspec(dllimport)
# define RRDEMOCLIB_LOCAL
#elif 4 <= __GNUC__
# define RRDEMOCLIB_EXPORT __attribute__((visibility("default")))
# define RRDEMOCLIB_IMPORT __attribute__((visibility("default")))
# define RRDEMOCLIB_LOCAL  __attribute__((visibility("hidden")))
#else
# define RRDEMOCLIB_IMPORT
# define RRDEMOCLIB_EXPORT
# define RRDEMOCLIB_LOCAL
#endif

#ifdef RRDEMO_C_LIB_EXPORTS
#   define RRDEMOCLIB_API RRDEMOCLIB_EXPORT
#else
#   define RRDEMOCLIB_API RRDEMOCLIB_IMPORT
#endif

#endif// _RRDEMOCLIB_DEF_H
