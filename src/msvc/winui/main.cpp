// App0.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CadWnd.h"
#include "CmdLineWnd.h"
#include "LogWnd.h"
#include "MainWnd.h"
#include "App0/Utility.h"
#include "App0/app0_exception.h"

using App0::RegisterDefWndClass;
using cadwin::CadWnd;
using cadwin::MainWnd;
using cadwin::CmdLineWnd;
using cadwin::LogWnd;

#define MAX_LOADSTRING 100

TCHAR* APP_CAPTION = _T("App0");

void __cdecl purecall_handler(){
  ::OutputDebugString(_T("pure function call\n"));
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
try {
  _set_purecall_handler(purecall_handler);
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  App0::InitGdiplus gdiplus;

  RegisterDefWndClass(MainWnd::CLASS_NAME);
  MainWnd mainWnd;
  mainWnd.SetTitle(_T("Testing"));
  RegisterDefWndClass(CadWnd::CLASS_NAME);
  CadWnd cadWnd(mainWnd.GetHandle());
  CmdLineWnd clWnd(mainWnd.GetHandle());
  LogWnd logWnd(mainWnd.GetHandle());

  MSG msg;
//	HACCEL hAccelTable;
  mainWnd.SetCad(&cadWnd);
  mainWnd.SetCmdLine(&clWnd);
  mainWnd.SetLog(&logWnd);
  mainWnd.Show(nCmdShow);
  mainWnd.Update();

  cad_core::cad_document<double> document;
  cad_win::cad_win_adaptor<double> gui(mainWnd);
  cad_core::cad_gui_view<double,
    cad_win::cad_win_adaptor<double> > view(document, gui);
  cadWnd.SetView(&view);
  //gtk_slate_set_view(slate, &view);

  // Initialize global strings
  // Main message loop:
  while (GetMessage(&msg, NULL, 0, 0))
  {
    //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //{
      TranslateMessage(&msg);
      DispatchMessage(&msg);
  	//}
  }

  return (int) msg.wParam;
}
catch(App0::app0_exception& ex){
  OutputDebugString(_T("Exception was caught\n"));
  ::MessageBox(0, ex.message(), APP_CAPTION, MB_OK);
  
  return 0;
}
