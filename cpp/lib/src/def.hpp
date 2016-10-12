/**
 * \file
 * \sa [Compilers Predefined Macros](http://sf.net/p/predef/wiki/Compilers/)
 * \sa [OSs Predefined Macros](http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system)
 * \sa [GCC Predefined Macros](http://gcc.gnu.org/onlinedocs/cpp/Predefined-Macros.html)
 * \sa [MSVC Predefined Macros](http://msdn.microsoft.com/library/b0084kay.aspx)
 * \author zhengrr
 * \date 2016-8-1 – 10-11
 * \copyright The MIT License
 */
#ifndef RRDEMO_CPP_LANG_DEF_H
#define RRDEMO_CPP_LANG_DEF_H

#if defined _WIN32 || defined __CYGWIN__
#   define RRDEMO_CPP_LANG_EXPORT __declspec(dllexport)
#   define RRDEMO_CPP_LANG_IMPORT __declspec(dllimport)
#   define RRDEMO_CPP_LANG_LOCAL
#elif 4 <= __GNUC__
#   define RRDEMO_CPP_LANG_EXPORT __attribute__((visibility("default")))
#   define RRDEMO_CPP_LANG_IMPORT __attribute__((visibility("default")))
#   define RRDEMO_CPP_LANG_LOCAL  __attribute__((visibility("hidden")))
#else
#   define RRDEMO_CPP_LANG_IMPORT
#   define RRDEMO_CPP_LANG_EXPORT
#   define RRDEMO_CPP_LANG_LOCAL
#endif

#ifdef RRDEMO_CPP_LANG_EXPORTS
#   define RRDEMO_CPP_LANG_API RRDEMO_CPP_LANG_EXPORT
#else
#   define RRDEMO_CPP_LANG_API RRDEMO_CPP_LANG_IMPORT
#endif

#endif// RRDEMO_CPP_LANG_DEF_H
