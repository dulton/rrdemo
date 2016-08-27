/* ************************************************************************//*!
 * \brief <stdio.h> Demo
 * \sa [stdio.h](http://cplusplus.com/reference/cstdio/)
 * \author zhengrr
 * \date 2016-6-30 ~ 7-15
 * \copyright The MIT License
 ******************************************************************************/

#include <stdio.h>

static FILE *fp = NULL;

void FileIO(void) {
   /* *****************************//*!
    * \brief File Open
    * \sa [fopen](http://en.cppreference.com/w/c/io/fopen)
    ***********************************/
   fp = fopen("file_path", "r");
   if (NULL == fp) { return; }  /* err */

   /* *****************************//*!
    * \brief File Close
    * \sa [fclose](http://en.cppreference.com/w/c/io/fclose)
    ***********************************/
   fclose(fp);
   if (!fp) { return; } /* err */
}
