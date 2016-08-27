/* ************************************************************************//*!
 * \brief LangC Test Case: <time.h>
 * \author zhengrr
 * \date 2016-8-8 ~ 11
 * \copyright The MIT License
 ******************************************************************************/
#include "testste_stdlib.h"

#include <stddef.h>

#include "check.h"

START_TEST(test_test) {
   /* empty */
} END_TEST

TCase *langc_testcase_time(void) {
   TCase *c = NULL;

   c = tcase_create("Case");
   tcase_add_test(c, test_test);

   return c;
}
