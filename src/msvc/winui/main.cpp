// App0.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "App0/App0.h"
#include "CadWnd.h"
#include "App0/app0_exception.h"

using App0::RegisterDefWndClass;
using cadwin::CadWnd;

#define MAX_LOADSTRING 100

TCHAR* APP_CAPTION = _T("App0");

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
try {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  RegisterDefWndClass(CadWnd::CLASS_NAME);
  CadWnd window;

  MSG msg;
//	HACCEL hAccelTable;
  window.Show(nCmdShow);
  window.Update();

  // Initialize global strings
  // Main message loop:
  while (GetMessage(&msg, NULL, 0, 0))
  {
    //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //{
      TranslateMessage(&msg);
      DispatchMessage(&msg);
//		}
  }

  return (int) msg.wParam;
}
catch(App0::app0_exception& ex){
  ::MessageBox(0, ex.message(), APP_CAPTION, MB_OK);
  
  return 0;
}
