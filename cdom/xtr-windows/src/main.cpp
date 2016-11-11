/**
 * \file
 * \author zhengrr
 * \date 2016-10-12 – 11-11
 * \copyright The MIT License
 */
#include <windows.h>
#include <tchar.h>

#if 1
/// Windows应用程序入口.
int _tmain(int argc, _TCHAR *argv[], _TCHAR *envp[])
{

}
#endif// SWITCH

#if 1
/// Windows图形应用程序入口.
/** \sa <http://msdn.microsoft.com/library/ms633559.aspx>
 */
int WINAPI _tWinMain(
    _In_ HINSTANCE hInstance,
    _In_ HINSTANCE hPrevInstance,
    _In_ LPTSTR lpCmdLine,
    _In_ int nCmdShow)
{
    MessageBox(NULL,
               _T("Hello World!"),
               _T("Just another Hello World program!"),
               MB_ICONEXCLAMATION | MB_OK);

}
#endif// SWITCH
