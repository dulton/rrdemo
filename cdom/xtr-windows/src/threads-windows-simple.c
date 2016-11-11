/** \file
 *  \sa [CreateThread](http://msdn.microsoft.com/library/ms682453.aspx)
 *  \sa [Sleep](http://msdn.microsoft.com/library/ms686298.aspx)
 *  \sa [WaitForSingleObject](http://msdn.microsoft.com/library/ms687032.aspx)
 *  \author zhengrr
 *  \date 2016-11-8
 *  \copyright The MIT License
 */
#ifdef _MSC_VER

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include <windows.h>

static DWORD WINAPI task(LPVOID data)
{
        const LPSTR name = (LPSTR)data;
        const int workload = 5;
        printf("%s: Ready to work!\n", name);
        for (int i = 1; i <= workload; ++i) {
                srand((unsigned)time(NULL));
                switch (rand() % 4) {
                case 0: printf("%s: Be happy to (%d/%d).\n", name, i, workload); break;
                case 1: printf("%s: I can do that (%d/%d).\n", name, i, workload); break;
                case 2: printf("%s: Okie dokie (%d/%d).\n", name, i, workload); break;
                case 3: printf("%s: Work, work (%d/%d).\n", name, i, workload); break;
                default: assert(false); abort();
                }
                Sleep(1000);
        }
        return 0;
}

#if 0
int main(void)
{
        HANDLE peon;
        if ((peon = CreateThread(NULL, 0, task, "Peon", 0, NULL))) {
                printf("Main: A peon has been produced.\n");
        } else {
                fprintf_s(stderr, "Thread creating failed.\n");
                exit(EXIT_FAILURE);
        }

        WaitForSingleObject(peon, INFINITE);
        printf("Main: The Peon work done.\n");

        system("pause");
        exit(EXIT_SUCCESS);
}
#endif// SWICH

#endif// MSVC
