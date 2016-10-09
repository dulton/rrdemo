/*!
 * \brief 布尔型
 * \sa [Type](http://en.cppreference.com/w/c/language/type)
 * \sa [stdbool.h](http://en.cppreference.com/w/c/types/boolean)
 * \author zhengrr
 * \date 2016-10-9
 * \copyright The MIT License
 ******************************************************************************/
#include <stdbool.h>  /*C99*/

#define BOOL int
#define TRUE 1
#define FALSE 0

/*!
 * \brief 布尔型
 * \since C89, C99
 **********************************************************/
void boolean_types(BOOL flag89, bool flag99) {
   /* C89 */
   if (flag89)
      flag89 = TRUE;
   if (!flag89)
      flag89 = FALSE;

   /* C99 */
   if (flag99)
      flag99 = true;
   if (!flag99)
      flag99 = false;
}
