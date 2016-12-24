/** \file
 *  \author zhengrr
 *  \date 2016-11-11 – 12-24
 *  \copyright The MIT License
 */
#include <stdio.h>

#include <tchar.h>
#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")

static int tmain(int argc, _TCHAR *argv[], _TCHAR *envp[])
{
        WSADATA data;  // Windows Socket Api Data
        if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &data)) {
                _tprintf_s(_T("Error at WSAStartup().\n"));
                return EXIT_FAILURE;
        }

        SOCKET skt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (INVALID_SOCKET == skt) {
                _tprintf_s(_T("Error at socket() with: %u.\n"), WSAGetLastError());
                WSACleanup();
                return EXIT_FAILURE;
        }

        SOCKADDR_IN addr;
        ZeroMemory(&addr, sizeof addr);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(10096);
        if (SOCKET_ERROR == bind(skt, (PSOCKADDR)&addr, sizeof addr)) {
                _tprintf_s(_T("Error at bind() with: %u.\n"), WSAGetLastError());
                closesocket(skt);
                WSACleanup();
                return EXIT_FAILURE;
        }

        DWORD optval;
        const DWORD optmask = 0x0000000000000011L;
        int optlen = sizeof optval;

        if (SOCKET_ERROR == getsockopt(skt, SOL_SOCKET, SO_KEEPALIVE, (char *)&optval, &optlen))
                _tprintf_s(_T("Error at getsockopt() with: %u.\n"), WSAGetLastError());
        else
                _tprintf_s(_T("SO_KEEPALIVE: %s.\n"), optval & optmask ? _T("ON") : _T("OFF"));

        optval = TRUE;
        if (SOCKET_ERROR == setsockopt(skt, SOL_SOCKET, SO_KEEPALIVE, (char *)&optval, optlen))
                _tprintf_s(_T("Error at setsockopt() with: %u.\n"), WSAGetLastError());
        else
                _tprintf_s(_T("Set SO_KEEPALIVE: %s.\n"), optval ? _T("ON") : _T("OFF"));

        if (SOCKET_ERROR == getsockopt(skt, SOL_SOCKET, SO_KEEPALIVE, (char *)&optval, &optlen))
                _tprintf_s(_T("Error at getsockopt() with: %u.\n"), WSAGetLastError());
        else
                _tprintf_s(_T("SO_KEEPALIVE: %s.\n"), optval & optmask ? _T("ON") : _T("OFF"));

        closesocket(skt);
        WSACleanup();
        return EXIT_SUCCESS;
}

#ifdef ENTRY_SWITCH
int _tmain(int argc, _TCHAR *argv[], _TCHAR *envp[]) { return tmain(argc, argv, envp); }
#endif// ENTRY SWITCH
