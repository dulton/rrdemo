/* ************************************************************************//*!
 * \file
 * \author zhengrr
 * \date 2016-8-17 ~ 18
 * \copyright The MIT License
 ******************************************************************************/
#ifndef LANGC_ASSERT_H
#define LANGC_ASSERT_H

#undef langc_assert

#ifdef NDEBUG
#  define langc_assert(e) ((void)0)
#else
#  include "except.h"
   extern const langc_except_t LANGC_ASSERT_FAILED;
#  define langc_assert(e) ((void)((e)||(LANGC_RAISE(LANGC_ASSERT_FAILED),0)))
   extern void (langc_assert)(int e);
#endif

#endif /* LANGC_ASSERT_H */
