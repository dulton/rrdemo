/**
 * \file
 * \author zhengrr
 * \date 2016-8-1 – 10-12
 * \copyright The MIT License
 */
#ifndef RRDEMO_C_LIB_DEF_H
#define RRDEMO_C_LIB_DEF_H

#ifdef _MSC_VER
#   define RRDEMO_C_LIB_EXPORT __declspec(dllexport)
#   define RRDEMO_C_LIB_IMPORT __declspec(dllimport)
#   define RRDEMO_C_LIB_LOCAL
#elif 4 <= __GNUC__
#   define RRDEMO_C_LIB_EXPORT __attribute__((visibility("default")))
#   define RRDEMO_C_LIB_IMPORT __attribute__((visibility("default")))
#   define RRDEMO_C_LIB_LOCAL  __attribute__((visibility("hidden")))
#else
#   define RRDEMO_C_LIB_IMPORT
#   define RRDEMO_C_LIB_EXPORT
#   define RRDEMO_C_LIB_LOCAL
#endif

#ifdef RRDEMO_C_LIB_EXPORTS
#   define RRDEMO_C_LIB_API RRDEMO_C_LIB_EXPORT
#else
#   define RRDEMO_C_LIB_API RRDEMO_C_LIB_IMPORT
#endif

#endif// RRDEMO_C_LIB_DEF_H
