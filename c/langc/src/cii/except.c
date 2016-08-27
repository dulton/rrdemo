/* ************************************************************************//*!
 * \copyright The MIT License
 ******************************************************************************/
#include "except.h"

#include <stdlib.h>
#include <stdio.h>

#include "assert.h"

langc_except_frame_t *langc_except_stack = NULL;

void langc_except_raise(const langc_except_t *e, const char *file, int line) {
   langc_assert(e);
   
   langc_except_frame_t *topframe = langc_except_stack;

   if (NULL == topframe) {
      fprintf(stderr, "Uncaught exception");

      if (e->reason) fprintf(stderr, " %s", e->reason);
      else fprintf(stderr, " at 0x%p", e);

      if (file && line > 0) fprintf(stderr, " raised at %s:%d", file, line);

      fprintf(stderr, "\naborting...\n");
      fflush(stderr);
      abort();
   }

   topframe->exception = e;
   topframe->file = file;
   topframe->line = line;

   LANGC_EXCEPT_STACK_POP;
   longjmp(topframe->env, LANGC_EXCEPT_RAISED);
}
