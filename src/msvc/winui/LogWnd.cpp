#include "stdafx.h"

#include "LogWnd.h"
#include "App0/Utility.h"

namespace cadwin {

LogWnd::LogWnd(HWND hwndParent) : Wnd0(_T("EDIT"), 0UL, _T(""),
  WS_CHILD | WS_BORDER | WS_VISIBLE | WS_VSCROLL
    | ES_MULTILINE | ES_WANTRETURN | ES_AUTOVSCROLL,
  0, 200, 300, 200, hwndParent){

  //HFONT hfont2 = (HFONT)::GetStockObject(ANSI_FIXED_FONT);
  hfont = App0::GetDefaultFont();
  if(hfont != 0)
    ::SendMessage(GetHandle(), WM_SETFONT, (WPARAM)hfont, MAKELPARAM(FALSE, 0));
}

LRESULT LogWnd::WndProc(UINT msg, WPARAM wParam, LPARAM lParam){
  WNDPROC baseWndProc = GetBaseWndProc();
  return baseWndProc(GetHandle(), msg, wParam, lParam);
}

LogWnd::~LogWnd(){
  ::DeleteObject(hfont);
}

}