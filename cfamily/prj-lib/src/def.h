/** \file
 *  \author zhengrr
 *  \date 2016-8-1 – 10-25
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCFAMILYLIB_DEF_H
#define _RRDEMOCFAMILYLIB_DEF_H

#if defined _MSC_VER || defined __CYGWIN__
# define RRDEMOCFAMILYLIB_EXPORT __declspec(dllexport)
# define RRDEMOCFAMILYLIB_IMPORT __declspec(dllimport)
# define RRDEMOCFAMILYLIB_LOCAL
#elif 4 <= __GNUC__
# define RRDEMOCFAMILYLIB_EXPORT __attribute__((visibility("default")))
# define RRDEMOCFAMILYLIB_IMPORT __attribute__((visibility("default")))
# define RRDEMOCFAMILYLIB_LOCAL  __attribute__((visibility("hidden")))
#else
# define RRDEMOCFAMILYLIB_IMPORT
# define RRDEMOCFAMILYLIB_EXPORT
# define RRDEMOCFAMILYLIB_LOCAL
#endif

#ifdef RRDEMO_CFAMILY_LIB_EXPORTS
# define RRDEMOCFAMILYLIB_API RRDEMOCFAMILYLIB_EXPORT
#else
# define RRDEMOCFAMILYLIB_API RRDEMOCFAMILYLIB_IMPORT
#endif

#endif// _RRDEMOCFAMILYLIB_DEF_H
