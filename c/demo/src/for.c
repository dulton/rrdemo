/*!
 * \file for.c
 * \brief for语句
 * \sa [for loop](http://en.cppreference.com/w/c/language/for)
 * \author zhengrr
 * \date 2016-10-9
 * \copyright The MIT License
 ******************************************************************************/

/*!
 * \brief for语句
 * \since C89, C99
 **********************************************************/
void for_statement(void) {
   /* C89 */
   int i89 = 0;
   for (i89 = 0; i89 < 9; ++i89) {
      continue;
   }

   /* C99 */
   for (int i99 = 0; i99 < 9; ++i99) {
      continue;
   }
}
