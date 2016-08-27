/* ************************************************************************//*!
 * \file
 * \author zhengrr
 * \date 2016-8-18
 * \copyright The MIT License
 ******************************************************************************/
#ifndef LANGC_MEM_H
#define LANGC_MEM_H

#include "except.h"

extern const langc_except_t LANGC_MEM_FAILED;

/* ****************************************************//*!
 * \brief LangC Mem Alloc
 * \since 2016-8-16
 **********************************************************/
extern void *langc_mem_alloc(long nbytes, const char *file, int line);
#define LANGC_ALLOC(nbytes) langc_mem_alloc((nbytes), __FILE__, __LINE__)
#define LANGC_NEW(p) ((p) = LANGC_ALLOC((long)sizeof *(p)))

/* ****************************************************//*!
 * \brief LangC Mem CAlloc
 * \since 2016-8-16
 **********************************************************/
extern void *langc_mem_calloc(
   long count, long nbytes, const char *file, int line);
#define LANGC_CALLOC(count, nbytes) langc_mem_calloc( \
   (count), (nbytes), __FILE__, __LINE__)
#define LANGC_NEW0(p) ((p) = LANGC_CALLOC(1, (long)sizeof *(p)))

/* ****************************************************//*!
 * \brief LangC Men Free
 * \since 2016-8-16
 **********************************************************/
extern void langc_mem_free(void *ptr, const char *file, int line);
#define LANGC_FREE(ptr) \
   ((void)(langc_mem_free((ptr), __FILE__, __LINE__), (ptr) = 0))

/* ****************************************************//*!
 * \brief LangC Men Resize
 * \since 2016-8-16
 **********************************************************/
extern void *langc_mem_resize(void *ptr, long nbytes, const char *file, int line);
#define LANGC_RESIZE(ptr, nbytes) \
   ((ptr) = langc_mem_resize((ptr), (nbytes), __FILE__, __LINE__))

#endif  /* LANGC_MEM_H */
