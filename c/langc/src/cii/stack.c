/* ************************************************************************//*!
 * \copyright The MIT License
 ******************************************************************************/
#include "stack.h"

#include <stddef.h>

#include "assert.h"
#include "mem.h"

struct langc_stack_t {
   int count;
   struct elem {
      void *x;
      struct elem *link;
   } *head;
};

langc_stack_t *langc_stack_new(void) {
   langc_stack_t *stk;
   LANGC_NEW(stk);
   stk->count = 0;
   stk->head = NULL;
   return stk;
}

int langc_stack_empty(langc_stack_t *stk) {
   langc_assert(stk);
   return 0 == stk->count;
}

void langc_stack_push(langc_stack_t *stk, void *x) {
   struct elem *t;
   langc_assert(stk);
   LANGC_NEW(t);
   t->x = x;
   t->link = stk->head;
   stk->head = t;
   stk->count++;
}

void *langc_stack_pop(langc_stack_t *stk) {
   void *x;
   struct elem *t;
   langc_assert(stk);
   langc_assert(stk->count > 0);
   t = stk->head;
   stk->head = t->link;
   stk->count--;
   x = t->x;
   LANGC_FREE(t);
   return x;
}

void langc_stack_free(langc_stack_t **stk) {
   struct elem *t, *u;
   langc_assert(stk && *stk);
   for (t = (*stk)->head; t; t = u) {
      u = t->link;
      LANGC_FREE(t);
   }
   LANGC_FREE(*stk);
}
