/** \file
 *  \brief 文件流.
 *  \author zhengrr
 *  \data 2016-11-7
 *  \copyright The MIT License
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * TEXTFILE: EndOfLine EndOfFile
 * MacOSnew     LF
 * MacOSold  CR
 * Unix         LF
 * Windows   CR LF     SUB
 */

#define TXT_FILE_NAME "test.txt"
#define BIN_FILE_NAME "test.bin"

#ifndef READ_TEST_FILE
int main(void)
{
        FILE *txtfp = NULL;
        FILE *binfp = NULL;

#if 201112L <= __STDC_VERSION__
        if (fopen_s(&txtfp, TXT_FILE_NAME, "a")) {
                printf("Can't open %s\n", TXT_FILE_NAME);
                exit(EXIT_FAILURE);
        }
        if (fopen_s(&binfp, BIN_FILE_NAME, "a")) {
                printf("Can't open %s\n", BIN_FILE_NAME);
                exit(EXIT_FAILURE);
        }
#else
        if (!(txtfp = fopen(TXT_FILE_NAME, "ab"))) {
                printf("Can't open %s\n", TXT_FILE_NAME);
                exit(EXIT_FAILURE);
        }
        if (!(binfp = fopen(BIN_FILE_NAME, "ab"))) {
                printf("Can't open %s\n", BIN_FILE_NAME);
                exit(EXIT_FAILURE);
        }
#endif

        fclose(txtfp);
        fclose(binfp);

        exit(EXIT_SUCCESS);
}
#endif