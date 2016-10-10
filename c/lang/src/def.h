/*!
 * \file
 * \author zhengrr
 * \date 2016-8-1 – 10-10
 * \copyright The MIT License
 ******************************************************************************/
#ifndef RRDEMO_C_LANG_DEF_H
#define RRDEMO_C_LANG_DEF_H

#if defined _WIN32 || defined __CYGWIN__
#   define RRDEMO_C_LANG_EXPORT __declspec(dllexport)
#   define RRDEMO_C_LANG_IMPORT __declspec(dllimport)
#   define RRDEMO_C_LANG_LOCAL
#elif 4 <= __GNUC__
#   define RRDEMO_C_LANG_EXPORT __attribute__((visibility("default")))
#   define RRDEMO_C_LANG_IMPORT __attribute__((visibility("default")))
#   define RRDEMO_C_LANG_LOCAL  __attribute__((visibility("hidden")))
#else
#   define RRDEMO_C_LANG_IMPORT
#   define RRDEMO_C_LANG_EXPORT
#   define RRDEMO_C_LANG_LOCAL
#endif

#ifdef RRDEMO_C_LANG_EXPORTS
#   define RRDEMO_C_LANG_API RRDEMO_C_LANG_EXPORT
#else
#   define RRDEMO_C_LANG_API RRDEMO_C_LANG_IMPORT
#endif

#endif// RRDEMO_C_LANG_DEF_H
