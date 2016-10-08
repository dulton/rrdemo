/* ************************************************************************//*!
 * \brief Test <string.h>
 * \sa [string.h](http://cplusplus.com/reference/cstring/)
 * \author zhengrr
 * \date 2016-6-27 ~ 8-5
 * \copyright The MIT License
 ******************************************************************************/
#include "testste_stdlib.h"

#include "check.h"

#include <stddef.h>
#include <string.h>

/* ****************************************************//*!
 * \brief Test Copying
 **********************************************************/
START_TEST(TestCopying) {
   char dst[9];

   /* *****************************//*!
    * \brief Memery Copy
    * \sa [memcpy](http://en.cppreference.com/w/c/string/byte/memcpy)
    ***********************************/
   memcpy(dst, "str\0free", 3);  /* str */
   memcpy(dst, "str\0free", 4);  /* str< */
   memcpy(dst, "str\0free", 9);  /* str<free< */

   /* *****************************//*!
    * \brief Memery Move
    * \sa [memmove](http://en.cppreference.com/w/c/string/byte/memmove)
    ***********************************/
   memmove(dst, "str\0free", 3);  /* str */
   memmove(dst, "str\0free", 4);  /* str< */
   memmove(dst, "str\0free", 9);  /* str<free< */

   /* *****************************//*!
    * \brief String Copy
    * \sa [strcpy](http://en.cppreference.com/w/c/string/byte/strcpy)
    ***********************************/
   strcpy(dst, "str\0free");  /* str< */

   /* *****************************//*!
    * \brief String N Copy
    * \sa [strncpy](http://en.cppreference.com/w/c/string/byte/strncpy)
    ***********************************/
   strncpy(dst, "str\0free", 3);  /* str */
   strncpy(dst, "str\0free", 4);  /* str< */
   strncpy(dst, "str\0free", 9);  /* str<<<<<< */
} END_TEST

/* ****************************************************//*!
 * \brief Test Concatenation
 **********************************************************/
 START_TEST(TestConcatenation) {
   char str1[8] = "str", str2[8] = "str", str3[8] = "str", str4[8] = "str";

   /* *****************************//*!
    * \brief String Cat
    * \sa [strcat](http://en.cppreference.com/w/c/string/byte/strcat)
    ***********************************/
   strcat(str1, "free");  /* strfree< */

   /* *****************************//*!
    * \brief String N Cat
    * \sa [strncat](http://en.cppreference.com/w/c/string/byte/strncat)
    ***********************************/
   strncat(str2, "free", 3);  /* strfre< */
   strncat(str3, "free", 4);  /* strfree< */
   strncat(str4, "free", 5);  /* strfree< */
} END_TEST

/* ****************************************************//*!
 * \brief Test Comparison
 **********************************************************/
 START_TEST(TestComparison) {
   const char b1204[] = {'\1', '\2', '\0', '4'};
   const char b1205[] = {'\1', '\2', '\0', '5'};
   const char b1304[] = {'\1', '\3', '\0', '4'};

   /* *****************************//*!
    * \brief Memery Compare
    * \sa [memcmp](http://en.cppreference.com/w/c/string/byte/memcmp)
    ***********************************/
   ck_assert_int_lt(memcmp(b1204, b1304, 2), 0);
   ck_assert_int_eq(memcmp(b1204, b1204, 2), 0);
   ck_assert_int_gt(memcmp(b1304, b1204, 2), 0);

   ck_assert_int_eq(memcmp(b1204, b1304, 1), 0);
   ck_assert_int_lt(memcmp(b1204, b1304, 2), 0);

   ck_assert_int_lt(memcmp(b1204, b1205, 4), 0);

   /* *****************************//*!
    * \brief String Compare
    * \sa [strcmp](http://en.cppreference.com/w/c/string/byte/strcmp)
    ***********************************/
   ck_assert_int_eq(strcmp(b1204, b1205), 0);

   /* *****************************//*!
    * \brief String N Compare
    * \sa [strncmp](http://en.cppreference.com/w/c/string/byte/strncmp)
    ***********************************/
   ck_assert_int_eq(strncmp(b1204, b1304, 1), 0);

   ck_assert_int_eq(strncmp(b1204, b1205, 4), 0);

   /* *****************************//*!
    * \brief String Coll
    * \sa [strcoll](http://en.cppreference.com/w/c/string/byte/strcoll)
    ***********************************/

   /* *****************************//*!
    * \brief String XFRM
    * \sa [strxfrm](http://en.cppreference.com/w/c/string/byte/strxfrm)
    ***********************************/
} END_TEST

/* ****************************************************//*!
 * \brief Test Searching
 **********************************************************/
 START_TEST(TestSearching) {
   const char b11305[] = {'\1', '\1', '\3', '\0', '\5'};

   /* *****************************//*!
    * \brief Memery Character
    * \sa [memchr](http://en.cppreference.com/w/c/string/byte/memchr)
    ***********************************/
   ck_assert_ptr_eq(memchr(b11305, '\3', 5), b11305 + (3 - 1));
   ck_assert_ptr_eq(memchr(b11305, '\6', 5), NULL);

   ck_assert_ptr_eq(memchr(b11305, '\3', 2), NULL);
   ck_assert_ptr_eq(memchr(b11305, '\3', 3), b11305 + (3 - 1));

   /* *****************************//*!
    * \brief String Character
    * \sa [strchr](http://en.cppreference.com/w/c/string/byte/strchr)
    ***********************************/
   ck_assert_ptr_eq(strchr(b11305, '\5'), NULL);

   /* *****************************//*!
    * \brief String Reverse Character
    * \sa [strrchr](http://en.cppreference.com/w/c/string/byte/strrchr)
    ***********************************/
   ck_assert_ptr_eq(strrchr(b11305, '\1'), b11305 + (2 - 1));

   /* *****************************//*!
    * \brief String P Break
    * \sa [strpbrk](http://en.cppreference.com/w/c/string/byte/strpbrk)
    ***********************************/
   ck_assert_ptr_eq(strpbrk(b11305, "\1\3\5"), b11305 + (1 - 1));
   ck_assert_ptr_eq(strpbrk(b11305, "\2\4\6"), NULL);
   ck_assert_ptr_eq(strpbrk(b11305, "\3\5\7"), b11305 + (3 - 1));

   /* *****************************//*!
    * \brief String Span
    * \sa [strspn](http://en.cppreference.com/w/c/string/byte/strspn)
    ***********************************/
   ck_assert_uint_eq(strspn(b11305, "\1\5"), 2);

   /* *****************************//*!
    * \brief String C Span
    * \sa [strcspn](http://en.cppreference.com/w/c/string/byte/strcspn)
    ***********************************/
   ck_assert_uint_eq(strcspn(b11305, "\3\7"), 2);

   /* *****************************//*!
    * \brief String String
    * \sa [strstr](http://en.cppreference.com/w/c/string/byte/strstr)
    ***********************************/
   ck_assert_ptr_eq(strstr(b11305, "\1\3"), b11305 + (2 - 1));

   /* *****************************//*!
    * \brief String Token
    * \sa [strtok](http://en.cppreference.com/w/c/string/byte/strtok)
    ***********************************/
} END_TEST

/* ****************************************************//*!
 * \brief Test Other
 **********************************************************/
 START_TEST(TestOther) {
   /* *****************************//*!
    * \brief Memery Set
    * \sa [memset](http://en.cppreference.com/w/c/string/byte/memset)
    ***********************************/

   /* *****************************//*!
    * \brief String Length
    * \sa [strlen](http://en.cppreference.com/w/c/string/byte/strlen)
    ***********************************/

   /* *****************************//*!
    * \brief String Error
    * \sa [strerror](http://en.cppreference.com/w/c/string/byte/strerror)
    ***********************************/
} END_TEST

TCase *TestcaseString(void) {
   TCase *c = NULL;

   c = tcase_create("String");  /* realese by suite runner */
   tcase_add_test(c, TestCopying);
   tcase_add_test(c, TestConcatenation);
   tcase_add_test(c, TestComparison);
   tcase_add_test(c, TestSearching);
   tcase_add_test(c, TestOther);

   return c;
}
