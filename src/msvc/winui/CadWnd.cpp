#include "stdafx.h"

#include "CadWnd.h"

namespace cadwin {

CadWnd::CadWnd() : BaseWnd(_T("CAD View")) {}

void CadWnd::OnWmPaint(HWND hwnd0){
  PAINTSTRUCT ps;
  ::BeginPaint(hwnd, &ps);
  ::OutputDebugString(_T("Painting..."));
  ::EndPaint(hwnd, &ps);
}

}