/* ************************************************************************//*!
 * \copyright The MIT License
 ******************************************************************************/
#include "mem.h"

#include <stddef.h>
#include <stdlib.h>

#include "assert.h"
#include "except.h"

const langc_except_t LANGC_MEM_FAILED = {"Allocation Failed"};

void *langc_mem_alloc(long nbytes, const char *file, int line) {
   void *ptr;
   langc_assert(nbytes > 0);
   ptr = malloc(nbytes);
   if (ptr == NULL) {
      if (file == NULL) LANGC_RAISE(LANGC_MEM_FAILED);
      else langc_except_raise(&LANGC_MEM_FAILED, file, line);
   }
   return ptr;
}

void *langc_mem_calloc(long count, long nbytes, const char *file, int line) {
   void *ptr;
   langc_assert(count > 0);
   langc_assert(nbytes > 0);
   ptr = calloc(count, nbytes);
   if (ptr == NULL) {
      if (file == NULL) LANGC_RAISE(LANGC_MEM_FAILED);
      else langc_except_raise(&LANGC_MEM_FAILED, file, line);
   }
   return ptr;
}

void langc_mem_free(void *ptr, const char *file, int line) {
   (void)file; (void)line;
   if (ptr) free(ptr);
}

void *langc_mem_resize(void *ptr, long nbytes, const char *file, int line) {
   langc_assert(ptr);
   langc_assert(nbytes > 0);
   ptr = realloc(ptr, nbytes);
   if (ptr == NULL) {
      if (file == NULL) LANGC_RAISE(LANGC_MEM_FAILED);
      else langc_except_raise(&LANGC_MEM_FAILED, file, line);
   }
   return ptr;
}