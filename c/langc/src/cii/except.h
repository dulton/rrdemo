/* ************************************************************************//*!
 * \file
 * \author zhengrr
 * \date 2016-8-16 ~ 18
 * \copyright The MIT License
 ******************************************************************************/
#ifndef LANGC_EXCEPT_H
#define LANGC_EXCEPT_H

#include <setjmp.h>

/* ****************************************************//*!
 * \brief LangC Except Type
 * \since 2016-8-16
 **********************************************************/
typedef struct langc_except_t {
   const char *reason;
} langc_except_t;

/* ****************************************************//*!
 * \brief LangC Except Frame Type
 * \since 2016-8-16
 **********************************************************/
typedef struct langc_except_frame_t {
   struct langc_except_frame_t *prev;
   jmp_buf                      env;
   const char                  *file;
   int                          line;
   const langc_except_t        *exception;
} langc_except_frame_t;

extern langc_except_frame_t *langc_except_stack;  /*!< LangC Except Stack */
#define LANGC_EXCEPT_STACK_PUSH(frame) \
do { frame.prev = langc_except_stack; \
     langc_except_stack = &frame; } while(0)
#define LANGC_EXCEPT_STACK_POP \
(langc_except_stack = langc_except_stack->prev)

/* ****************************************************//*!
 * \brief
 * \since 2016-8-16
 **********************************************************/
enum {
   LANGC_EXCEPT_ENTERED = 0,
   LANGC_EXCEPT_RAISED,
   LANGC_EXCEPT_HANDLED,
   LANGC_EXCEPT_FINALIZED
};

/* ****************************************************//*!
 * \brief LangC Except Raise
 * \since 2016-8-16
 **********************************************************/
void langc_except_raise(const langc_except_t *e, const char *file, int line);

/* ****************************************************//*!
 * \brief RAISE
 * \since 2016-8-16
 **********************************************************/
#define LANGC_RAISE(e) langc_except_raise(&(e), __FILE__, __LINE__)

/* ****************************************************//*!
 * \brief TRY-EXCEPT-ELSE-FINALLY-END_TRY
 * \since 2016-8-16
 **********************************************************/
#define LANGC_RERAISE langc_except_raise(langc_except_frame.exception, \
                                         langc_except_frame.file, \
                                         langc_except_frame.line)

#define LANGC_RETURN switch (LANGC_EXCEPT_STACK_POP, 0) \
                     default: return

#define LANGC_TRY \
do { \
   volatile int langc_except_flag; \
   langc_except_frame_t langc_except_frame; \
   LANGC_EXCEPT_STACK_PUSH(langc_except_frame); \
   langc_except_flag = setjmp(langc_except_frame.env); \
   if (LANGC_EXCEPT_ENTERED == langc_except_flag) {

#define LANGC_EXCEPT(e) \
      if (LANGC_EXCEPT_ENTERED == langc_except_flag) LANGC_EXCEPT_STACK_POP; \
   } else if (&(e) == langc_except_frame.exception) { \
      langc_except_flag = LANGC_EXCEPT_HANDLED;

#define LANGC_ELSE \
      if (LANGC_EXCEPT_ENTERED == langc_except_flag) LANGC_EXCEPT_STACK_POP; \
   } else { \
      langc_except_flag = LANGC_EXCEPT_HANDLED;

#define LANGC_FINALLY \
      if (LANGC_EXCEPT_ENTERED == langc_except_flag) LANGC_EXCEPT_STACK_POP; \
   } { \
      if (LANGC_EXCEPT_ENTERED == langc_except_flag) \
         langc_except_flag = LANGC_EXCEPT_FINALIZED;

#define LANGC_END_TRY \
      if (LANGC_EXCEPT_ENTERED == langc_except_flag) LANGC_EXCEPT_STACK_POP; \
   } if (LANGC_EXCEPT_RAISED == langc_except_flag) RERAISE; \
} while (0)

#endif  /* LANGC_EXCEPT_H */
