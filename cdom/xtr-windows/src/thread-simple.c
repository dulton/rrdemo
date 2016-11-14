/** \file
 *  \sa [CreateThread](http://msdn.microsoft.com/library/ms682453.aspx)
 *  \sa [Sleep](http://msdn.microsoft.com/library/ms686298.aspx)
 *  \sa [WaitForSingleObject](http://msdn.microsoft.com/library/ms687032.aspx)
 *  \author zhengrr
 *  \date 2016-11-8
 *  \copyright The MIT License
 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include <tchar.h>
#include <windows.h>

static DWORD WINAPI task(LPVOID data)
{
    const LPTSTR name = (LPTSTR)data;
    const int workload = 5;
    _tprintf(_T("%s: Ready to work!\n"), name);
    for (int i = 1; i <= workload; ++i) {
        srand((unsigned)time(NULL));
        switch (rand() % 4) {
        case 0: _tprintf(_T("%s: Be happy to (%d/%d).\n"), name, i, workload); break;
        case 1: _tprintf(_T("%s: I can do that (%d/%d).\n"), name, i, workload); break;
        case 2: _tprintf(_T("%s: Okie dokie (%d/%d).\n"), name, i, workload); break;
        case 3: _tprintf(_T("%s: Work, work (%d/%d).\n"), name, i, workload); break;
        default: assert(false); abort();
        }
        Sleep(1000);
    }
    return 0;
}

#if ENTRY_SWITCH || 1
int _tmain(void)
{
    HANDLE peon;
    if ((peon = CreateThread(NULL, 0, task, _T("Peon"), 0, NULL))) {
        _tprintf(_T("Main: A peon has been produced.\n"));
    } else {
        _ftprintf_s(stderr, _T("Thread creating failed.\n"));
        exit(EXIT_FAILURE);
    }

    WaitForSingleObject(peon, INFINITE);
    _tprintf(_T("Main: The Peon work done.\n"));

    _tsystem(_T("pause"));

    exit(EXIT_SUCCESS);
}
#endif// ENTRY SWITCH
