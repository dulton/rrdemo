/**
 * \file
 * \brief 程序入口
 * \author zhengrr
 * \date 2016-10-12 – 14
 * \copyright The MIT License
 */
#include <windows.h>

/**
 * \brief 程序入口
 * \sa http://msdn.microsoft.com/library/windows/desktop/ms633559.aspx
 */
int WINAPI WinMain(
      _In_ HINSTANCE hInstance,
      _In_ HINSTANCE hPrevInstance,
      _In_ LPSTR lpCmdLine,
      _In_ int nCmdShow) {

   MessageBox(NULL,
              "Hello World!",
              "Just another Hello World program!",
              MB_ICONEXCLAMATION | MB_OK);

}
