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
#ifndef RRDEMO_CPP_LANG_DEF_HPP
#define RRDEMO_CPP_LANG_DEF_HPP

#if 199409L <= __cplusplus
#   define CPP14 201402L
#endif
#if 201103L <= __cplusplus
#   define CPP11 201103L
#endif
#if 199711L <= __cplusplus
#   define CPP98 199711L
#endif

#endif// RRDEMO_CPP_LANG_DEF_HPP
