#include "StdAfx.h"
#include "Wnd0.h"
#include "Utility.h"

#include "app0_exception.h"
#include <comdef.h>

namespace App0 {

  TCHAR* ERR_CLASS_NOT_REGISTERED = _T("Window class not registered.");
  TCHAR* ERR_CLASS_REGISTRATION_FAILED = _T("Failed to register class.");
  TCHAR* ERR_WINDOW_CREATION_FAILED = _T("Window creation failed.");

  Wnd0::Wnd0(HWND hwnd) : hwnd(hwnd) {
    Init();
  }

  Wnd0::Wnd0(LPCTSTR lpClassName, DWORD dwExStyle, LPCWSTR lpWindowName,
    DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hwndParent,
    HMENU hMenu) : hwnd(0)
  {

    hwnd = CreateWindowEx(dwExStyle, lpClassName, lpWindowName,
      dwStyle, X, Y, nWidth, nHeight, hwndParent, hMenu,
      GetModuleHandle(0), this);

    LogLastError();

    if(hwnd == 0)
      throw app0_exception(ERR_WINDOW_CREATION_FAILED);

    Init();

  }

  BOOL Wnd0::Show(int nCmdShow){
    return ::ShowWindow(hwnd, nCmdShow);
  }

  BOOL Wnd0::Update(){
    return UpdateWindow(hwnd);
  }

  Wnd0::~Wnd0()
  {
    if(hwnd == 0) return;
    ::DestroyWindow(hwnd);
  }

  ATOM RegisterDefWndClass(LPCTSTR lpClassName){
    WNDCLASSEX wcex;

    wcex.cbClsExtra = wcex.cbWndExtra = 0;
    wcex.cbSize = sizeof(wcex);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
    HINSTANCE hInstance = ::GetModuleHandle(NULL);

    wcex.hIcon = 0 /*(HICON) ::LoadImage(hInstance, MAKEINTRESOURCE(IDI_APP0),
      IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON),
      LR_SHARED)*/;

    wcex.hIconSm = 0 /*(HICON) ::LoadImage(hInstance, MAKEINTRESOURCE(IDI_APP0),
      IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON),
      ::GetSystemMetrics(SM_CYSMICON), LR_SHARED)*/;

    wcex.hInstance = hInstance;
    wcex.lpfnWndProc = DefWindowProc;
    wcex.lpszClassName = lpClassName;
    wcex.lpszMenuName = NULL;
    wcex.style = CS_HREDRAW | CS_VREDRAW;

    return ::RegisterClassEx(&wcex);
  }

  BOOL Wnd0::SetTitle(const TCHAR* title){
    return SetWindowText(hwnd, title);
  }

  BOOL Wnd0::Init(){
    if(hwnd == 0)
      return FALSE;

    ::SetLastError(0);
    LONG_PTR prevData = ::GetWindowLongPtr(hwnd, GWL_USERDATA);
    if(prevData != 0)
      return FALSE;

    ::SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG) this);
    if(::GetLastError() != 0)
      return FALSE;

    LONG_PTR prev = ::SetWindowLongPtr(hwnd, GWL_WNDPROC,
      (LONG)App0::Wnd0_WndProc);

    baseWndProc = (WNDPROC) prev;

    return TRUE;
  }

  LRESULT CALLBACK Wnd0_WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam){
    assert(hwnd != 0);

    LONG_PTR ptr = ::GetWindowLongPtr(hwnd, GWL_USERDATA);
    Wnd0* window = reinterpret_cast<Wnd0*>(ptr);
    if(window == 0)
      throw app0_exception(_T("Object pointer is 0."));

    return window->WndProc(msg, wParam, lParam);
  }

  //LRESULT Wnd0::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
  //  LONG_PTR ptr = ::GetWindowLongPtr(hwnd, GWL_USERDATA);
  //  Wnd0* window = reinterpret_cast<Wnd0*>(ptr);
  //  if(window == 0)
  //    throw app0_exception(_T("Object pointer is 0."));

  //  return window->WndProc(msg, wParam, lParam);
  //}

  LRESULT Wnd0::WndProc(UINT msg, WPARAM wParam, LPARAM lParam){

    switch(msg){
      HANDLE_MSG(hwnd, WM_NCDESTROY, OnWmNCDestroy);
    }

    return baseWndProc(hwnd, msg, wParam, lParam);
  }

  void Wnd0::OnWmNCDestroy(HWND hwnd){
    this->hwnd = 0;
  }

  void Wnd0::Destroy(){
    assert(hwnd != 0);
    if(hwnd == 0) return;
    ::DestroyWindow(hwnd);
  }

  Wnd0::operator HWND(){
    return hwnd;
  }

}