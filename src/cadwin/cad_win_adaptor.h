#ifndef WIN_ADAPTOR_H_INCLUDED
#define WIN_ADAPTOR_H_INCLUDED

#include <Windows.h>
#include <cassert>
#include "cad_exception.h"

#include "cad_gdiplus_adaptor.h"

namespace cad_win {

using cad_core::cad_exception;

class TmpDC {
  HDC hdc;
  HWND hwnd;

public:
  TmpDC(HWND hwnd) : hwnd(hwnd) {
    hdc = ::GetDC(hwnd);
    if(hdc == 0)
      throw cad_exception("GetDC failed");
  }

  operator HDC(){
    return hdc;
  }

  ~TmpDC(){
    ::ReleaseDC(hwnd, hdc);
  }

};


template<typename T> class cad_win_graphics;

template<typename T> class cad_win_adaptor {
  HWND hwnd;
public:
  typedef cad_gdiplus_adaptor<T> graphics_type;

  cad_win_adaptor(HWND hwnd) : hwnd(hwnd) {
  }

  void get_mouse_position(int &x, int &y){
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(hwnd, &p);
    x = (int)p.x;
    y = (int)p.y;
  }

  HWND get_hwnd(){
    return hwnd;
  }

  void invalidate(){
    InvalidateRect(hwnd, 0, FALSE);
  }

  bool loop;
  void run_event_loop(){
    loop = true;

    MSG msg;

    while (loop && GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
  }

  void exit_event_loop(){
    loop = false;
  }
};

}

#endif  // WIN_ADAPTOR_H_INCLUDED