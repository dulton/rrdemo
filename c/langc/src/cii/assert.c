/* ************************************************************************//*!
 * \copyright The MIT License
 ******************************************************************************/
#include "assert.h"

const langc_except_t LANGC_ASSERT_FAILED = {"Assertion Failed"};

void (langc_assert)(int e) {
   langc_assert(e);
}
