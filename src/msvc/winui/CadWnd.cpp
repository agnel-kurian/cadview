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
    HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
    HANDLE_MSG(hwnd, WM_MOUSEMOVE, OnMouseMove);
    HANDLE_MSG(hwnd, WM_LBUTTONDOWN, OnLButtonDown);
    HANDLE_MSG(hwnd, WM_LBUTTONUP, OnLButtonUp);
    HANDLE_MSG(hwnd, WM_MBUTTONDOWN, OnMButtonDown);
    HANDLE_MSG(hwnd, WM_MBUTTONUP, OnMButtonUp);
    HANDLE_MSG(hwnd, WM_RBUTTONUP, OnRButtonUp);
  }

  return baseWndProc(hwnd, msg, wParam, lParam);
}

void CadWnd::OnPaint(HWND){
  HWND hwnd = GetHandle();
  PAINTSTRUCT ps;
  ::BeginPaint(hwnd, &ps);

  view_type::graphics_type graphics(ps.hdc);
  view->paint(graphics);

  ::EndPaint(hwnd, &ps);

}

void CadWnd::OnMouseMove(HWND, int x, int y, UINT keyFlags){
  view->mouse_move(x, y);
}

void CadWnd::OnLButtonDown(HWND hwnd, BOOL fDoubleClick,
  int x, int y, UINT keyFlags){

  view->mouse_down(cad_core::Mouse_button_Left, x, y);

}

void CadWnd::OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags){
  view->mouse_up(cad_core::Mouse_button_Left, x, y);
}

void CadWnd::OnMButtonDown(HWND hwnd, BOOL fDoubleClick,
  int x, int y, UINT keyFlags){

  view->mouse_down(cad_core::Mouse_button_Middle, x, y);

}

void CadWnd::OnMButtonUp(HWND hwnd, int x, int y, UINT flags){
  view->mouse_up(cad_core::Mouse_button_Middle, x, y);
}

void CadWnd::OnRButtonUp(HWND hwnd, int x, int y, UINT flags){
  view->mouse_up(cad_core::Mouse_button_Right, x, y);
}


void CadWnd::SetView(view_type* view){
  this->view = view;
}

}
