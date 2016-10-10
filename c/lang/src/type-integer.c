/*!
 * \brief 整型
 * \sa http://en.cppreference.com/w/c/language/type
 * \author zhengrr
 * \date 2016-10-9
 * \copyright The MIT License
 ******************************************************************************/

/*
 * C89
 ******************************************************************************/
#ifdef __STDC__

#include <limits.h>

/*!
 * \brief C89中的整型
 * \sa [limits.h](http://en.cppreference.com/w/c/types/limits)
 * \since C89
 **********************************************************/
void rrdemo_c_lang_integer_in_c89(void) {
   signed short int ssi = (short) 0;
   unsigned short int usi = (unsigned short) 0;

   signed int si = 0;
   unsigned int ui = 0u;

   signed long int sli = 0L;
   unsigned long int uli = 0uL;

   signed long long int slli = 0LL;  //C99
   unsigned long long int ulli = 0uLL;  //C99
}

#endif// C89

/*
 * C99
 ******************************************************************************/
#if 199901L <= __STDC_VERSION__

#include <stdint.h>

/*!
 * \brief C99中的整型
 * \sa [stdint.h](http://en.cppreference.com/w/c/types/integer)
 * \since C99
 **********************************************************/
void rrdemo_c_lang_integer_in_c99(void) {
   signed long long int slli = 0LL;  //C99
   unsigned long long int ulli = 0uLL;  //C99
}

#endif// C99
