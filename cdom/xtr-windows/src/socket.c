/** \file
 *  \author zhengrr
 *  \date 2016-11-11
 *  \copyright The MIT License
 */
#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")

#ifdef ENTRY_SWITCH
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
#endif// ENTRY SWITCH
