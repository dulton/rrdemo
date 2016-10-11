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
#ifndef RDCL_DEF_H
#define RDCL_DEF_H

#if defined _WIN32 || defined __CYGWIN__
#   define RDCL_EXPORT __declspec(dllexport)
#   define RDCL_IMPORT __declspec(dllimport)
#   define RDCL_LOCAL
#elif 4 <= __GNUC__
#   define RDCL_EXPORT __attribute__((visibility("default")))
#   define RDCL_IMPORT __attribute__((visibility("default")))
#   define RDCL_LOCAL  __attribute__((visibility("hidden")))
#else
#   define RDCL_IMPORT
#   define RDCL_EXPORT
#   define RDCL_LOCAL
#endif

#ifdef RRDEMO_C_LANG_EXPORTS
#   define RDCL_API RDCL_EXPORT
#else
#   define RDCL_API RDCL_IMPORT
#endif

#endif// RDCL_DEF_H
