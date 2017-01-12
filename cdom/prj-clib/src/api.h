/** \file
 *  \author zhengrr
 *  \date 2016-8-1 – 2017-1-12
 *  \copyright The MIT License
 */
#ifndef RRDEMO__CDOM__C_LIBRARY__API_H
#define RRDEMO__CDOM__C_LIBRARY__API_H

#if defined _MSC_VER || defined __CYGWIN__
# define RRDEMO__CDOM__C_LIBRARY__EXPORT __declspec(dllexport)
# define RRDEMO__CDOM__C_LIBRARY__IMPORT __declspec(dllimport)
# define RRDEMO__CDOM__C_LIBRARY__LOCAL
#elif 4 <= __GNUC__
# define RRDEMO__CDOM__C_LIBRARY__EXPORT __attribute__((visibility("default")))
# define RRDEMO__CDOM__C_LIBRARY__IMPORT __attribute__((visibility("default")))
# define RRDEMO__CDOM__C_LIBRARY__LOCAL __attribute__((visibility("hidden")))
#else
# define RRDEMO__CDOM__C_LIBRARY__EXPORT
# define RRDEMO__CDOM__C_LIBRARY__IMPORT
# define RRDEMO__CDOM__C_LIBRARY__LOCAL
#endif

#ifdef RRDEMO__CDOM__C_LIBRARY__EXPORTS
# define RRDEMO__CDOM__C_LIBRARY__API RRDEMO__CDOM__C_LIBRARY__EXPORT
#else
# define RRDEMO__CDOM__C_LIBRARY__API RRDEMO__CDOM__C_LIBRARY__IMPORT
#endif

#endif// RRDEMO__CDOM__C_LIBRARY__API_H
