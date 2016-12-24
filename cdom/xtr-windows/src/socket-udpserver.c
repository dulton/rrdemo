/** \file
 *  \author zhengrr
 *  \date 2016-12-24
 *  \copyright The MIT License
 */
#include <stdio.h>

#include <WinSock2.h>
#include <tchar.h>

#pragma comment(lib, "Ws2_32.lib")

static int tmain(int argc, _TCHAR *argv[], _TCHAR *envp[])
{
        _tprintf_s(_T("*** Startuping Windows Socket..."));
        WSADATA data;
        int rwsas = WSAStartup(MAKEWORD(2, 2), &data);  // Result of WSAStartup
        if (NO_ERROR != rwsas) {
                _tprintf_s(_T(" ! WSAStartup() failed with error %d.\n"), rwsas);
                return EXIT_FAILURE;
        }
        _tprintf_s(_T(" Startuped.\n"));

        _tprintf_s(_T("*** Creating Socket..."));
        SOCKET skt = socket(AF_INET, SOCK_DGRAM, 0);
        if (INVALID_SOCKET == skt) {
                _tprintf_s(_T(" ! socket() failed with error %d.\n"), WSAGetLastError());
                WSACleanup();
                return EXIT_FAILURE;
        }
        _tprintf_s(_T(" Created.\n"));

        _tprintf_s(_T("*** Binding address..."));
        SOCKADDR_IN addr;
        ZeroMemory(&addr, sizeof addr);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(10096);
        if (SOCKET_ERROR == bind(skt, (PSOCKADDR)&addr, sizeof addr)) {
                _tprintf_s(_T(" ! bind() failed with error %d.\n"), WSAGetLastError());
                closesocket(skt);
                WSACleanup();
                return EXIT_FAILURE;
        }
        _tprintf_s(_T(" Binded with port %hu.\n"), ntohs(addr.sin_port));

        char buf[512];
        while (TRUE) {
                _tprintf_s(_T("*** Waiting for data..."));
                ZeroMemory(buf, sizeof buf);
                SOCKADDR_IN ano;
                int anolen = sizeof ano;
                int datalen;

                datalen = recvfrom(skt, buf, sizeof buf, 0, (PSOCKADDR)&ano, &anolen);
                if (SOCKET_ERROR == datalen) {
                        _tprintf_s(_T(" ! recvfrom() failed with error %d.\n"), WSAGetLastError());
                        closesocket(skt);
                        WSACleanup();
                        return EXIT_FAILURE;
                }

                _tprintf_s(_T("\n >> Received packet from %hhu.%hhu.%hhu.%hhu:%hu.\n"),
                           ano.sin_addr.s_net, ano.sin_addr.s_host, ano.sin_addr.s_lh, ano.sin_addr.s_impno, ntohs(ano.sin_port));
                _tprintf_s(_T("    Message: %s\n"), buf);

                _tprintf_s(_T("  < Sending echo..."));
                if (SOCKET_ERROR == sendto(skt, buf, datalen, 0, (PSOCKADDR)&ano, anolen)) {
                        _tprintf_s(_T(" ! sendto() failed with error %d.\n"), WSAGetLastError());
                        closesocket(skt);
                        WSACleanup();
                        return EXIT_FAILURE;
                }
                _tprintf_s(_T(" Sended.\n"));
        }

        closesocket(skt);

        WSACleanup();

        return EXIT_SUCCESS;
}

#ifdef ENTRY_SWITCH
int _tmain(int argc, _TCHAR *argv[], _TCHAR *envp[]) { return tmain(argc, argv, envp); }
#endif// ENTRY SWITCH
