#include "stdafx.h"

#include "MainWnd.h"

namespace cadwin {

const TCHAR *MainWnd::CLASS_NAME = _T("9A9DC997-C098-4B3A-9EC3-842078268F55");

MainWnd::MainWnd() : Wnd0(CLASS_NAME, 0, _T("CAD View")) {}

LRESULT MainWnd::WndProc(UINT msg, WPARAM wParam, LPARAM lParam){
  HWND hwnd = GetHandle();
  switch(msg){
    HANDLE_MSG(hwnd, WM_CLOSE, OnWmClose);
    HANDLE_MSG(hwnd, WM_DESTROY, OnWmDestroy);
  }

  //  do not call inherited static WndProc here! will cause recursion.
  return Wnd0::WndProc(msg, wParam, lParam);
}

void MainWnd::OnWmPaint(HWND){
  HWND hwnd = GetHandle();
  PAINTSTRUCT ps;
  ::BeginPaint(hwnd, &ps);
  ::OutputDebugString(_T("Painting...\n"));
  ::EndPaint(hwnd, &ps);
}

void MainWnd::OnWmClose(HWND){
  Destroy();
}

void MainWnd::OnWmDestroy(HWND){
  ::PostQuitMessage(0);
}

MainWnd::~MainWnd(){
  OutputDebugString(
    boost::str(
      tformat(_T("MainWnd::~MainWnd() : %p \n")) % this
      ).c_str());
}

}