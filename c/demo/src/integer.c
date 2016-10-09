/*!
 * \brief 整型
 * \sa [Type](http://en.cppreference.com/w/c/language/type)
 * \sa [limits.h](http://en.cppreference.com/w/c/types/limits)
 * \sa [stdint.h](http://en.cppreference.com/w/c/types/integer)
 * \author zhengrr
 * \date 2016-10-9
 * \copyright The MIT License
 ******************************************************************************/
#include <limits.h>
#include <stdint.h>  /*C99*/

/*!
 * \brief 整型
 * \since C89, C99
 **********************************************************/
void integer_types(void) {
   signed short int ssi = (short) 0;
   unsigned short int usi = (unsigned short) 0;

   signed int si = 0;
   unsigned int ui = 0u;

   signed long int sli = 0L;
   unsigned long int uli = 0uL;

   signed long long int slli = 0LL;  /*C99*/
   unsigned long long int ulli = 0uLL;  /*C99*/
}
