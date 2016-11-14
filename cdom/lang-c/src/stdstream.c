/** \file
 *  \brief 标准输入输出流。
 *  \author zhengrr
 *  \date 2016-11-14
 *  \copyright The MIT License
 */
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

/* ------------------------------------------------------------------ *
 * Unformatted input/output
 * ------------------------------------------------------------------ */

#if ENTRY_SWITCH || 0
/** \brief GET CHARacter / PUT CHARacter
 *  \sa <http://en.cppreference.com/w/c/io/getchar>
 *  \sa <http://en.cppreference.com/w/c/io/putchar>
 */
int main(void)
{
        char ch;
        while (EOF != (ch = getchar()))
                if (EOF == putchar(ch)) {
                        perror("putchar()");
                        return EXIT_FAILURE;
                };

        if (feof(stdin)) {
                if (EOF == puts("End of file reached.")) {
                        perror("puts()");
                        return EXIT_FAILURE;
                }
        } else if (ferror(stdin)) {
                perror("getchar()");
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}
#endif// ENTRY SWITCH

#if ENTRY_SWITCH || 0
/** \brief GET Wide CHARacter / PUT Wide CHARacter
 *  \sa <http://en.cppreference.com/w/c/io/getwchar>
 *  \sa <http://en.cppreference.com/w/c/io/putwchar>
 */
int main(void)
{
        setlocale(LC_ALL, "");
        wchar_t wch;
        while ((wch = getwchar()) != WEOF)
                if (WEOF == putwchar(wch)) {
                        perror("putwchar()");
                        return EXIT_FAILURE;
                }

        if (feof(stdin)) {
                if (EOF == puts("End of file reached.")) {
                        perror("puts()");
                        return EXIT_FAILURE;
                }
        } else if (ferror(stdin)) {
                perror("getwchar()");
                return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
}
#endif// ENTRY SWITCH

#if ENTRY_SWITCH || 0
/** \brief GET String / PUT String
 *  \sa <http://en.cppreference.com/w/c/io/gets>
 *  \sa <http://en.cppreference.com/w/c/io/puts>
 */
int main(void)
{
        char buf[256];
#if 201112L<=__STDC_VERSION__
        if (!gets_s(buf, (rsize_t)(sizeof buf / sizeof *buf))) {
#else
        if (!gets(buf)) {
#endif
                if (feof(stdin)) {
                        if (EOF == puts("End of file reached.")) {
                                perror("puts()");
                                return EXIT_FAILURE;
                        }
                } else {// ferror(stdin)
                        perror("getchar()");
                        return EXIT_FAILURE;
                }

        }

        if (EOF == puts(buf)) {
                perror("puts()");
                return EXIT_FAILURE;
        }

        system("pause");
        return EXIT_SUCCESS;
        }
#endif// ENTRY SWITCH

/* ------------------------------------------------------------------ *
 * Formatted input/output
 * ------------------------------------------------------------------ */

#if ENTRY_SWITCH || 0
/** \brief SCAN Formatted input / PRINT Formatted output
 *  \sa <http://en.cppreference.com/w/c/io/fscanf>
 *  \sa <http://en.cppreference.com/w/c/io/fprintf>
 */
int main(void)
{
        setlocale(LC_ALL, "");
        char buf[256];
#if 201112L<=__STDC_VERSION__||1
        scanf_s("%s", buf, (rsize_t)(sizeof buf / sizeof *buf));
        printf_s("%s", buf);
#else
        scanf("%s", buf);
        printf("%s", buf);
#endif
        system("pause");
        return EXIT_SUCCESS;
}
#endif// ENTRY SWITCH

#if ENTRY_SWITCH || 0
/** \brief Wide SCAN Formatted input / Wide PRINT Formatted output
 *  \sa <http://en.cppreference.com/w/c/io/fwscanf>
 *  \sa <http://en.cppreference.com/w/c/io/fwprintf>
 */
int main(void)
{
        setlocale(LC_ALL, "");
        wchar_t buf[256];
#if 201112L<=__STDC_VERSION__
        wscanf_s(L"%ls", buf, (rsize_t)(sizeof buf / sizeof *buf));
        wprintf_s(L"%ls", buf);
#else
        wscanf(L"%ls", buf);
        wprintf(L"%ls", buf);
#endif
        system("pause");
        return EXIT_SUCCESS;
}
#endif// ENTRY SWITCH
