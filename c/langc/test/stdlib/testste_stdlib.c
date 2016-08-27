/* ************************************************************************//*!
 * \copyright The MIT License
 ******************************************************************************/
#include "testste_stdlib.h"

#include <stddef.h>

int langc_testste_stdlib(void) {
   Suite *ste = NULL;
   SRunner *run = NULL;
   int num = 0;

   ste = suite_create("Suite"); /* ste */
   suite_add_tcase(ste, testcase_case());

   run = srunner_create(ste); /* run */
   srunner_run_all(run, CK_NORMAL);
   num = srunner_ntests_failed(run); /* num */
   srunner_free(run);

   return num;
}
