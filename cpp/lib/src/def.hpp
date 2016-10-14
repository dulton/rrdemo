/**
 * \file
 * \author zhengrr
 * \date 2016-8-1 – 10-12
 * \copyright The MIT License
 */
#ifndef RRDEMO_CPP_LIB_DEF_H
#define RRDEMO_CPP_LIB_DEF_H

#if defined _WIN32 || defined __CYGWIN__
#   define RRDEMO_CPP_LIB_EXPORT __declspec(dllexport)
#   define RRDEMO_CPP_LIB_IMPORT __declspec(dllimport)
#   define RRDEMO_CPP_LIB_LOCAL
#elif 4 <= __GNUC__
#   define RRDEMO_CPP_LIB_EXPORT __attribute__((visibility("default")))
#   define RRDEMO_CPP_LIB_IMPORT __attribute__((visibility("default")))
#   define RRDEMO_CPP_LIB_LOCAL  __attribute__((visibility("hidden")))
#else
#   define RRDEMO_CPP_LIB_IMPORT
#   define RRDEMO_CPP_LIB_EXPORT
#   define RRDEMO_CPP_LIB_LOCAL
#endif

#ifdef RRDEMO_CPP_LIB_EXPORTS
#   define RRDEMO_CPP_LIB_API RRDEMO_CPP_LIB_EXPORT
#else
#   define RRDEMO_CPP_LIB_API RRDEMO_CPP_LIB_IMPORT
#endif

#endif// RRDEMO_CPP_LIB_DEF_H
