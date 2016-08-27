/* ************************************************************************//*!
 * \file
 * \brief LangC Test Suite: Standard Library
 * \author zhengrr
 * \date 2016-8-5 ~ 11
 * \copyright The MIT License
 ******************************************************************************/
#ifndef LANGC_TESTSTE_STDLIB_H
#define LANGC_TESTSTE_STDLIB_H

#include "check.h"

/* ****************************************************//*!
 * \brief LangC Test Case: <time.h>
 * \return The pointer to TCase.
 * \post Need realese the TCase.
 * \since 2016-8-8
 **********************************************************/
TCase *langc_testcase_time(void);

/* ****************************************************//*!
 * \brief Test Suite: Standard Library
 * \return "Number of all tests run by the suite runner".
 * \since 2016-8-5
 **********************************************************/
int langc_testste_stdlib(void);

#endif  /* LANGC_TESTSTE_STDLIB_H */
