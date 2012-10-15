#include "stdafx.h"

#include "CadWnd.h"
#include "LogWnd.h"
#include "CmdLineWnd.h"

#include "MainWnd.h"
#include "App0/Utility.h"

#include "resource.h"

namespace cadwin {

const TCHAR *MainWnd::CLASS_NAME = _T("9A9DC997-C098-4B3A-9EC3-842078268F55");

//Wnd0(LPCTSTR wndClass, DWORD dwExStyle = 0,
//  LPCTSTR lpWindowName = _T(""), DWORD dwStyle = WS_OVERLAPPEDWINDOW,
//  int X = CW_USEDEFAULT, int Y = CW_USEDEFAULT,
//  int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT,
//  HWND hwndParent = 0, HMENU hMenu = 0);

MainWnd::MainWnd() : Wnd0(CLASS_NAME, 0, _T("CAD View"), WS_OVERLAPPEDWINDOW,
  CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0,
  ::LoadMenu(::GetModuleHandle(0), MAKEINTRESOURCE(IDR_MAINWND_MENU))),
  cl(0), log(0) {

}

LRESULT MainWnd::WndProc(UINT msg, WPARAM wParam, LPARAM lParam){
  HWND hwnd = GetHandle();
  switch(msg){
    HANDLE_MSG(hwnd, WM_CLOSE, OnClose);
    HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
    HANDLE_MSG(hwnd, WM_SIZE, OnSize);
    HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
    HANDLE_MSG(hwnd, WM_MOUSEWHEEL, OnMouseWheel);
  }

  //  do not call inherited static WndProc here! will cause recursion.
  return Wnd0::WndProc(msg, wParam, lParam);
}

void MainWnd::OnPaint(HWND){
  HWND hwnd = GetHandle();
  PAINTSTRUCT ps;
  ::BeginPaint(hwnd, &ps);
  ::EndPaint(hwnd, &ps);
}

void MainWnd::OnClose(HWND){
  Destroy();
}

void MainWnd::OnDestroy(HWND){
  ::PostQuitMessage(0);
}

void MainWnd::OnSize(HWND, UINT state, int cx, int cy){
  HWND hwnd = *this;
  RECT rect;
  ::GetClientRect(hwnd, &rect);
  int clHeight = App0::GetTextHeight(hwnd);
  int logHeight = clHeight * 5;
  int cheight = rect.bottom - rect.top;
  int cwidth = rect.right - rect.left;

  int cadHeight = cheight - clHeight - logHeight;

  ::MoveWindow(*cad, 0, 0, cwidth, cadHeight, FALSE);
  ::MoveWindow(*cl, 0, cadHeight, cwidth, clHeight, FALSE);
  ::MoveWindow(*log, 0, cadHeight + clHeight, cwidth, logHeight, FALSE);
  ::InvalidateRect(hwnd, 0, FALSE);
}

MainWnd::~MainWnd(){
}

void MainWnd::SetCmdLine(CmdLineWnd* cl){
  this->cl = cl;
}

void MainWnd::SetLog(LogWnd* log){
  this->log = log;
}

void MainWnd::SetCad(CadWnd* cad){
  this->cad = cad;
}

void MainWnd::OnCommand(HWND, int id, HWND hwndCtl, UINT codeNotify){
  switch(id){
  case ID_FILE_POLYLINE:
    GetCad().GetView()->run_polyline_cmd();
    break;
  case ID_FILE_SELECT:
    GetCad().GetView()->run_select_cmd();
    break;
  case ID_FILE_EXIT:
    ::DestroyWindow(*this);
    break;
  }
}

void MainWnd::OnMouseWheel(HWND hwnd, int xPos, int yPos,
  int zDelta, UINT fwKeys){

  cad_core::Mouse_scroll_direction dir = (zDelta < 0)
    ? cad_core::Mouse_scroll_direction_Down
      : cad_core::Mouse_scroll_direction_Up;
  POINT cp = { xPos, yPos };
  if(ScreenToClient(*cad, &cp))
    cad->GetView()->mouse_scroll(dir, cp.x, cp.y);

}


}