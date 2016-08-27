/* ************************************************************************//*!
 * \file
 * \author zhengrr
 * \date 2016-8-17
 * \copyright The MIT License
 ******************************************************************************/
#ifndef LANGC_STACK_H
#define LANGC_STACK_H

typedef struct langc_stack_t langc_stack_t;
extern langc_stack_t *langc_stack_new(void);
extern int langc_stack_empty(langc_stack_t *stk);
extern void langc_stack_push(langc_stack_t *stk, void *x);
extern void *langc_stack_pop(langc_stack_t *stk);
extern void langc_stack_free(langc_stack_t **stk);

#endif  /* LANGC_STACK_H */
