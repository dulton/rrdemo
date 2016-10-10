/*!
 * \file
 * \brief for（语句）
 * \sa http://en.cppreference.com/w/c/language/for
 * \author zhengrr
 * \date 2016-10-9 – 10-10
 * \copyright The MIT License
 ******************************************************************************/

/*
 * C89
 ******************************************************************************/
#ifdef __STDC__

/*!
 * \brief C89中的for（语句）
 * \since C89
 **********************************************************/
void rrdemo_c_lang_for_in_c89(void) {
   int i = 0;
   for (i = 0; i < 9; ++i) {
      continue;
   }
}

#endif// C89

/*
 * C99
 ******************************************************************************/
#if 199901L <= __STDC_VERSION__

/*!
 * \brief C99中的for（语句）
 * \since C99
 **********************************************************/
void rrdemo_c_lang_for_in_c99(void) {
   for (int i = 0; i < 9; ++i) {
      continue;
   }
}

#endif// C99
