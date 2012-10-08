#include "stdafx.h"
#include "CmdLineWnd.h"
#include "App0/Utility.h"

using App0::TmpDC;

namespace cadwin {

CmdLineWnd::CmdLineWnd(HWND hwndParent) : Wnd0(_T("EDIT"), 0UL, _T(""),
  WS_CHILD | WS_BORDER | WS_VISIBLE,
  300, 0, 300, 200, hwndParent){

  //HFONT hfont2 = (HFONT)::GetStockObject(ANSI_FIXED_FONT);
  hfont = App0::GetDefaultFont();
  if(hfont != 0)
    ::SendMessage(GetHandle(), WM_SETFONT, (WPARAM)hfont, MAKELPARAM(FALSE, 0));

  HWND hwnd = GetHandle();
  int height = App0::GetTextHeight(hwnd) + 2;
  ::MoveWindow(hwnd, 0, 0, 300, height, FALSE);
}

LRESULT CmdLineWnd::WndProc(UINT msg, WPARAM wParam, LPARAM lParam){
  WNDPROC baseWndProc = GetBaseWndProc();
  return baseWndProc(GetHandle(), msg, wParam, lParam);
}

CmdLineWnd::~CmdLineWnd(){
  ::DeleteObject(hfont);
}

}
