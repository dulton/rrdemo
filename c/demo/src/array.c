/*!
 * \brief 数组
 * \sa [Array](http://en.cppreference.com/w/c/language/array)
 * \author zhengrr
 * \date 2016-10-9
 * \copyright The MIT License
 ******************************************************************************/

/*!
 * \brief 数组初始化
 * \sa [Array Initialization](http://en.cppreference.com/w/c/language/array_initialization)
 * \since C89, C99
 **********************************************************/
void array_initialization(void) {
   /* C89 */
   int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   /*    10:    1, 2, 3, 4, 5, 6, 7, 8, 9, 10 */
   int b[10] = {1, 2, 3};
   /*    10:    1, 2, 3, 0, 0, 0, 0, 0, 0, 0 */
   int c[10] = {0};
   /*    10:    0, 0, 0, 0, 0, 0, 0, 0, 0, 0 */

   int d[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   /*   10:   1, 2, 3, 4, 5, 6, 7, 8, 9, 10 */

   /* C99 */
   int e[10] = {[1] = 2, [3] = 4};
   /*    10:    0, 2, 0, 4, 0, 0, 0, 0, 0, 0 */
}
