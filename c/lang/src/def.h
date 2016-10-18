/**
 * \file
 * \sa [Compilers Predefined Macros](http://sf.net/p/predef/wiki/Compilers/)
 * \sa [OSs Predefined Macros](http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system)
 * \sa [GCC Predefined Macros](http://gcc.gnu.org/onlinedocs/cpp/Predefined-Macros.html)
 * \sa [MSVC Predefined Macros](http://msdn.microsoft.com/library/b0084kay.aspx)
 * \author zhengrr
 * \date 2016-10-18
 * \copyright The MIT License
 */
#ifndef RRDEMO_C_LANG_DEF_H
#define RRDEMO_C_LANG_DEF_H

#if 201112L <= __STDC_VERSION__
#   define C11 201112L
#endif
#if 199901L <= __STDC_VERSION__
#   define C99 199901L
#endif
#if 199409L <= __STDC_VERSION__
#   define C95 199409L
#endif
#if defined __STDC__
#   define C89 1990L
#endif

#endif// RRDEMO_C_LANG_DEF_H
