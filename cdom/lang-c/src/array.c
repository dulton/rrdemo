/** \file
 *  \brief 数组。
 *  \sa <http://en.cppreference.com/w/c/language/array>
 *  \sa <http://en.cppreference.com/w/c/language/array_initialization>
 *  \sa <http://sglib.sourceforge.net/doc/index.html#array_api0>
 *  \author zhengrr
 *  \date 2016-10-9 – 11-14
 *  \copyright The MIT License
 */
#include <string.h>
#ifdef SGLIB

#include <stdio.h>
#include <stdlib.h>

#include "sglib/sglib.h"

#define SIZE 10
static int INPUT[SIZE] = {1, 7, 5, 3, 9, 0, 6, 4, 2, 8};

#ifdef ENTRY_SWITCH
int main(void)
{
        int array[SIZE];
        for (int i = 0; i < SIZE; ++i) {
                array[i] = INPUT[i];
        }

        SGLIB_ARRAY_SINGLE_QUICK_SORT(int, array, SIZE, SGLIB_NUMERIC_COMPARATOR);

        for (int i = 0; i < SIZE; i++) {
                printf("%d ", array[i]);
        }
        printf("\n");
        return EXIT_SUCCESS;
}

#endif// ENTRY SWICH

#endif// SGLIB
