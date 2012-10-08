#include "stdafx.h"
#include "CmdLineWnd.h"
#include "App0/Utility.h"

namespace cadwin {
  LPCTSTR CmdLineWnd::CLASS_NAME = _T("EDIT");
CmdLineWnd::CmdLineWnd(HWND hwndParent) : Wnd0(CLASS_NAME, 0UL, _T(""),
  WS_CHILD | WS_BORDER | WS_VISIBLE,
  300, 0, 300, 200, hwndParent){

  hfont = App0::GetDefaultFont();
  if(hfont != 0)
    ::SendMessage(GetHandle(), WM_SETFONT, (WPARAM)hfont, MAKELPARAM(FALSE, 0));
}

LRESULT CmdLineWnd::WndProc(UINT msg, WPARAM wParam, LPARAM lParam){
  WNDPROC baseWndProc = GetBaseWndProc();
  return baseWndProc(GetHandle(), msg, wParam, lParam);
}

CmdLineWnd::~CmdLineWnd(){
  ::DeleteObject(hfont);
}

}
