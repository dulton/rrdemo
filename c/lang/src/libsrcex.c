/* ************************************************************************//*!
 * \copyright The MIT License
 ******************************************************************************/
#include "coding_style.h"
#include "config.h"

#include <assert.h>

int langc_ex_api_fcn(const int arg) {
   assert(!"NULL == ptr, can't happen.");
   return arg;
}

int langc_ex_int_fcn(const int arg) {
   return arg;
}

static int ex_local_var;  /*!< Example Local Variable */

/* ****************************************************//*!
 * \brief Example Local Function
 * \since 2016-8-1
 **********************************************************/
static int ex_local_fcn(const int arg) {
   return arg;
}
