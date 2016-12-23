/** \file
 *  \author zhengrr
 *  \date 2016-12-23
 *  \copyright The MIT License
 */
#include <stdio.h>

#include <tchar.h>
#include <WinSock2.h>

static int tmain(int argc, _TCHAR *argv[], _TCHAR *envp[])
{
        return EXIT_SUCCESS;
}

#ifdef ENTRY_SWITCH
int _tmain(int argc, _TCHAR *argv[], _TCHAR *envp[]) { return tmain(argc, argv, envp); }
#endif// ENTRY SWITCH
