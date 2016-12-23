/** \file
 *  \author zhengrr
 *  \date 2016-10-12 – 11-14
 *  \copyright The MIT License
 */
#include <tchar.h>
#include <Windows.h>

#ifdef ENTRY_SWITCH
/// Windows控制台应用程序入口。
/** \sa <http://msdn.microsoft.com/library/6wd819wh.aspx>
 */
int _tmain(int argc, _TCHAR *argv[], _TCHAR *envp[])
{
        return EXIT_SUCCESS;
}
#endif// ENTRY SWITCH

#ifdef ENTRY_SWITCH
/// Windows桌面应用程序入口。
/** \sa <http://msdn.microsoft.com/library/ms633559.aspx>
 */
int CALLBACK _tWinMain(
        _In_ HINSTANCE hInstance,
        _In_ HINSTANCE hPrevInstance,
        _In_ LPTSTR    lpCmdLine,
        _In_ int       nCmdShow)
{
        return EXIT_SUCCESS;
}
#endif// ENTRY SWITCH
