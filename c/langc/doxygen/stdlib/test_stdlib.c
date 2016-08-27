/* ************************************************************************//*!
 * \brief <stdlib.h> Demo
 * \sa [stdlib.h](http://cplusplus.com/reference/cstdlib/)
 * \author zhengrr
 * \date 2016-7-1
 * \copyright The MIT License
 ******************************************************************************/

#include <stdlib.h>

#include <errno.h>
#include <time.h>

/* ****************************************************//*!
 * \brief String Conversion
 **********************************************************/
void StringConversion(void) {
   /* *****************************//*!
    * \brief A To Int
    * \deprecated Replaced by strtol.
    * \sa [atoi](http://en.cppreference.com/w/c/string/byte/atoi)
    ***********************************/
   atoi("0");  /* int */

   /* *****************************//*!
    * \brief A To Long
    * \deprecated Replaced by strtol.
    * \sa [atol](http://en.cppreference.com/w/c/string/byte/atoi)
    ***********************************/
   atol("0");  /* long */

   /* *****************************//*!
    * \brief A To Long Long
    * \deprecated Replaced by strtoll.
    * \since C99
    * \sa [atoll](http://en.cppreference.com/w/c/string/byte/atoi)
    ***********************************/
   atoll("0");  /* long long */

   /* *****************************//*!
    * \brief A To Float
    * \deprecated Replaced by strtod.
    * \since C99
    * \sa [atof](http://en.cppreference.com/w/c/string/byte/atof)
    ***********************************/
   atof("0.");  /* double */

   /* *****************************//*!
    * \brief String To Long
    * \sa [strtol](http://en.cppreference.com/w/c/string/byte/strtol)
    ***********************************/
   errno = 0;
   char *endptr = NULL;
   strtol("0", endptr, 10);  /* long */
   if (ERANGE == errno) { /*invalid*/; }
   errno = 0;
   if ('\0' == *endptr) { /*consumed*/ }

   /* *****************************//*!
    * \brief String To Unsigned Long
    * \sa [strtoul](http://en.cppreference.com/w/c/string/byte/strtoul)
    ***********************************/
   strtoul("0", NULL, 10);  /* unsigned long */

   /* *****************************//*!
    * \brief String To Long Long
    * \since C99
    * \sa [strtoll](http://en.cppreference.com/w/c/string/byte/strtol)
    ***********************************/
   strtoll("0", NULL, 10);  /* long long */

   /* *****************************//*!
    * \brief String To Unsigned Long Long
    * \sa [strtoull](http://en.cppreference.com/w/c/string/byte/strtoul)
    ***********************************/
   strtoull("0", NULL, 10);  /* unsigned long long */

   /* *****************************//*!
    * \brief String To Float
    * \since C99
    * \sa [strtof](http://en.cppreference.com/w/c/string/byte/strtof)
    ***********************************/
   strtof("0.", NULL);  /* float */

   /* *****************************//*!
    * \brief String To Double
    * \sa [strtod](http://en.cppreference.com/w/c/string/byte/strtof)
    ***********************************/
   strtod("0.", NULL);  /* double */

   /* *****************************//*!
    * \brief String To Long Double
    * \since C99
    * \sa [strtod](http://en.cppreference.com/w/c/string/byte/strtof)
    ***********************************/
   strtold("0.", NULL);  /* long double */
}

/* ****************************************************//*!
 * \brief Pseudo-Random Sequence Generation
 **********************************************************/
void PseudoRandomSequenceGeneration(void) {
   srand(time(NULL));
   rand();
}
