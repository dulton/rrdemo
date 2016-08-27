/* ************************************************************************//*!
 * \file
 * \author zhengrr
 * \date 2016-8-5 ~ 8
 * \copyright The MIT License
 ******************************************************************************/
#include <assert.h>
#include <stdlib.h>

#include "stdlib/testste_stdlib.h"

/* ****************************************************//*!
 * \brief Entry Point
 * \param argc Argument count.
 * \param argv Argument vector.
 * \return Exit status.
 **********************************************************/
int main(void) {
   int tot = 0;
   int i = 0;

   i = langc_testste_suite();  assert(0 <= i);  tot += i;

   system("pause");
   return (0 < tot) ? EXIT_FAILURE : EXIT_SUCCESS;
}
