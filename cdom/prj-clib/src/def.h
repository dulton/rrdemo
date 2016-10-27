/** \file
 *  \author zhengrr
 *  \date 2016-8-1 – 10-27
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMCLIB_DEF_H
#define _RRDEMOCDOMCLIB_DEF_H

#if defined _MSC_VER || defined __CYGWIN__
# define RRDEMOCDOMCLIB_EXPORT __declspec(dllexport)
# define RRDEMOCDOMCLIB_IMPORT __declspec(dllimport)
# define RRDEMOCDOMCLIB_LOCAL
#elif 4 <= __GNUC__
# define RRDEMOCDOMCLIB_EXPORT __attribute__((visibility("default")))
# define RRDEMOCDOMCLIB_IMPORT __attribute__((visibility("default")))
# define RRDEMOCDOMCLIB_LOCAL  __attribute__((visibility("hidden")))
#else
# define RRDEMOCDOMCLIB_IMPORT
# define RRDEMOCDOMCLIB_EXPORT
# define RRDEMOCDOMCLIB_LOCAL
#endif

#ifdef RRDEMOCDOMCLIB_EXPORTS
# define RRDEMOCDOMCLIB_API RRDEMOCDOMCLIB_EXPORT
#else
# define RRDEMOCDOMCLIB_API RRDEMOCDOMCLIB_IMPORT
#endif

#endif// _RRDEMOCDOMCLIB_DEF_H
