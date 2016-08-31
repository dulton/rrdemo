/* ************************************************************************//*!
 * \file
 * \author zhengrr
 * \date 2016-8-1 ~ 10
 * \copyright The MIT License
 ******************************************************************************/
#ifndef LANGC_CODINGSTYLE_H
#define LANGC_CODINGSTYLE_H

#if defined _WIN32 || defined __CYGWIN__
#   define LANGC_EXPORT __declspec(dllexport)
#   define LANGC_IMPORT __declspec(dllimport)
#   define LANGC_LOCAL
#elif __GNUC__ >= 4
#   define LANGC_EXPORT __attribute__((visibility("default")))
#   define LANGC_IMPORT __attribute__((visibility("default")))
#   define LANGC_LOCAL  __attribute__((visibility("hidden")))
#else
#   define LANGC_IMPORT
#   define LANGC_EXPORT
#   define LANGC_LOCAL
#endif

#ifdef LANGC_EXPORTS
#   define LANGC_API LANGC_EXPORT
#else
#   define LANGC_API LANGC_IMPORT
#endif

/* ****************************************************//*!
 * \brief LangC Example API Function
 * \since 2016-8-1
 **********************************************************/
LANGC_API extern int langc_ex_api_fcn(const int param);

#endif  /* LANGC_CODINGSTYLE_H */
