#ifndef LOGWND_INCLUDED
#define LOGWND_INCLUDED

#include "App0/Wnd0.h"

using App0::Wnd0;

namespace cadwin {

class LogWnd : public Wnd0 {
  HFONT hfont;
protected:
  virtual LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);
public:
  LogWnd(HWND hwndParent);
  ~LogWnd();
};

}

#endif