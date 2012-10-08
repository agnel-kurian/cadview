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

  switch(msg){
    HANDLE_MSG(hwnd, WM_PAINT, OnWmPaint);
    HANDLE_MSG(hwnd, WM_MOUSEMOVE, OnWmMouseMove);
    HANDLE_MSG(hwnd, WM_LBUTTONDOWN, OnWmLButtonDown);
    HANDLE_MSG(hwnd, WM_LBUTTONUP, OnWmLButtonUp);
    HANDLE_MSG(hwnd, WM_MBUTTONDOWN, OnWmMButtonDown);
    HANDLE_MSG(hwnd, WM_MBUTTONUP, OnWmMButtonUp);
    HANDLE_MSG(hwnd, WM_RBUTTONUP, OnWmRButtonUp);
    HANDLE_MSG(hwnd, WM_MOUSEWHEEL, OnWmMouseWheel);
  }

  return baseWndProc(hwnd, msg, wParam, lParam);
}

void CadWnd::OnWmPaint(HWND){
  HWND hwnd = GetHandle();
  PAINTSTRUCT ps;
  ::BeginPaint(hwnd, &ps);

  view_type::graphics_type graphics(ps.hdc);
  view->paint(graphics);

  ::EndPaint(hwnd, &ps);

}

void CadWnd::OnWmMouseMove(HWND, int x, int y, UINT keyFlags){
  view->mouse_move(x, y);
}

void CadWnd::OnWmLButtonDown(HWND hwnd, BOOL fDoubleClick,
  int x, int y, UINT keyFlags){

  view->mouse_down(cad_core::Mouse_button_Left, x, y);

}

void CadWnd::OnWmLButtonUp(HWND hwnd, int x, int y, UINT keyFlags){
  view->mouse_up(cad_core::Mouse_button_Left, x, y);
}

void CadWnd::OnWmMButtonDown(HWND hwnd, BOOL fDoubleClick,
  int x, int y, UINT keyFlags){

  view->mouse_down(cad_core::Mouse_button_Middle, x, y);

}

void CadWnd::OnWmMButtonUp(HWND hwnd, int x, int y, UINT flags){
  view->mouse_up(cad_core::Mouse_button_Middle, x, y);
}

void CadWnd::OnWmRButtonUp(HWND hwnd, int x, int y, UINT flags){
  view->mouse_up(cad_core::Mouse_button_Right, x, y);
}

void CadWnd::OnWmMouseWheel(HWND hwnd, int xPos, int yPos,
  int zDelta, UINT fwKeys){

  cad_core::Mouse_scroll_direction dir = (zDelta < 0)
    ? cad_core::Mouse_scroll_direction_Down
      : cad_core::Mouse_scroll_direction_Up;
  view->mouse_scroll(dir, xPos, yPos);

}

void CadWnd::SetView(view_type* view){
  this->view = view;
}

}
