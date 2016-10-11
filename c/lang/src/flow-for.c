/**
 * \file
 * \brief for
 * \sa http://en.cppreference.com/w/c/language/for
 * \author zhengrr
 * \date 2016-10-9 – 10-11
 * \copyright The MIT License
 */

/*============================================================================*
 * C89
 *============================================================================*/
#ifdef __STDC__

static void c89for(void) {
   int i = 0;
   for (i = 0; i < 9; ++i) {
      continue;
   }
}

#endif// C89

/*============================================================================*
 * C99
 *============================================================================*/
#if 199901L <= __STDC_VERSION__

static void c99for(void) {
   for (int i = 0; i < 9; ++i) {
      continue;
   }
}

#endif// C99
