/** \file
 *  \sa <http://sf.net/p/predef/wiki/Compilers/>
 *  \sa <http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system>
 *  \sa <http://gcc.gnu.org/onlinedocs/cpp/Predefined-Macros.html>
 *  \sa <http://msdn.microsoft.com/library/b0084kay.aspx>
 *  \author zhengrr
 *  \date 2016-10-18 – 31
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMCPP_DEF_HPP
#define _RRDEMOCDOMCPP_DEF_HPP

#if 199409L<=__cplusplus
# define CPP14 201402L
#endif
#if 201103L<=__cplusplus
# define CPP11 201103L
#endif
#if 199711L<=__cplusplus
# define CPP98 199711L
#endif

#endif// _RRDEMOCDOMCPP_DEF_HPP
