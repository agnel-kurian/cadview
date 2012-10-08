#pragma once

namespace App0 {

  extern TCHAR* ERR_CLASS_NOT_REGISTERED;
  extern TCHAR* ERR_CLASS_REGISTRATION_FAILED;
  extern TCHAR* ERR_WINDOW_CREATION_FAILED;

  ATOM RegisterDefWndClass(LPCTSTR lpClassName);

  class Wnd0 {
    WNDPROC baseWndProc;
    HWND hwnd;
  protected:
    WNDPROC GetBaseWndProc() const { return baseWndProc; }
    virtual LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);
  public:
    Wnd0(HWND hwnd); //  wraps around hwnd ...and subclasses it?
    Wnd0(LPCTSTR wndClass, DWORD dwExStyle = 0,
      LPCTSTR lpWindowName = _T(""), DWORD dwStyle = WS_OVERLAPPEDWINDOW,
      int X = CW_USEDEFAULT, int Y = CW_USEDEFAULT,
      int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT,
      HWND hwndParent = 0, HMENU hMenu = 0);  //  creates hwnd based on existing window class
    //  we do not provide default that automatically registers a class
    //  we can provide separate class whose only job is to provide default
    //  window class with default overridable settings and registers itself
    //  that class can have conversion functions to WNDCLASSEX and TCHAR*

    //  initialization:
    //  set window proc to static BaseWnd_WndProc
    //  add a property to hold the this pointer
    //  in the virtual destructor we clear the property
    //  all messages received by the window till the class' window proc has been
    //  installed cannot be handled here. we'll fix that some other day

    BOOL Init();

    //  message handling:
    //  

    BOOL SetTitle(const TCHAR* title);

    //virtual void OnWmClose(HWND hwnd);
    virtual void OnWmNCDestroy(HWND hwnd);
    BOOL Show(int nCmdShow);
    BOOL Update();

    void Destroy();
    virtual ~Wnd0();
    operator HWND();

    HWND GetHandle() const { return hwnd; }

    friend LRESULT CALLBACK Wnd0_WndProc(HWND hwnd, UINT msg,
      WPARAM wParam, LPARAM lParam);
  };

  //  retrieves c++ object pointer from hwnd
  //  forwards all messages to member functions
  LRESULT CALLBACK Wnd0_WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam);

}