/** \file
 *  \sa <http://sglib.sourceforge.net/doc/index.html#list_api0>
 *  \author zhengrr
 *  \date 2016-11-11
 *  \copyright The MIT License
 */
#ifdef SGLIB

#include <stdio.h>
#include <stdlib.h>

#include "sglib/sglib.h"

#define SIZE_OF_ARRAY(array) (sizeof(array) / sizeof(array[0]))

typedef struct int_list_elem {
        int i;
        struct int_list_elem *next_ptr;
} int_list_elem, *int_list;

#define ILIST_COMPARATOR(e1, e2) (e1->i - e2->i)

#if 1
int main(void)
{
        int input[] = {1, 5, 3, 7, 9, 6, 3, 5, 2, 11, 85, 991};

        int_list list = NULL;
        int_list_elem *cur;
        for (int i = 0; i < SIZE_OF_ARRAY(input); ++i) {
                cur = malloc(sizeof(int_list_elem));
                cur->i = input[i];
                SGLIB_LIST_ADD(int_list_elem, list, cur, next_ptr);
        }

        SGLIB_LIST_REVERSE(int_list_elem, list, next_ptr);

        SGLIB_LIST_SORT(int_list_elem, list, ILIST_COMPARATOR, next_ptr);

        SGLIB_LIST_MAP_ON_ELEMENTS(int_list_elem, list, cur, next_ptr, {
                printf("%d ", cur->i);
        });
        printf("\n");

        SGLIB_LIST_MAP_ON_ELEMENTS(int_list_elem, list, cur, next_ptr, {
                free(cur);
        });
        system("pause");
        return(0);
}
#endif// SWICH

#endif// SGLIB
