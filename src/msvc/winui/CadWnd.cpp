#include "stdafx.h"
#include "CadWnd.h"

namespace cadwin {

LPCTSTR CadWnd::CLASS_NAME = _T("d859fe14-026b-467a-89d6-e49e3fe8465b");

CadWnd::CadWnd(HWND hwndParent) : Wnd0(CLASS_NAME, 0UL, _T("CAD View"),
  WS_CHILD | WS_BORDER | WS_VISIBLE,
  0, 0, 300, 200, hwndParent){
}

LRESULT CadWnd::WndProc(UINT msg, WPARAM wParam, LPARAM lParam){
  HWND hwnd = GetHandle();
  WNDPROC baseWndProc = GetBaseWndProc();
  return baseWndProc(hwnd, msg, wParam, lParam);
}

}
