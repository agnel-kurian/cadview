#pragma once

#include "App0/Wnd0.h"

using App0::Wnd0;

namespace cadwin {

class CmdLineWnd : public Wnd0 {
  HFONT hfont;
protected:
  virtual LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

  static LPCTSTR CLASS_NAME;
public:
  CmdLineWnd(HWND hwndParent);
  ~CmdLineWnd();
};

}