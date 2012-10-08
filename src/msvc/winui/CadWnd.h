#pragma once

#include "App0/Wnd0.h"

using App0::Wnd0;

namespace cadwin {

class CadWnd : public Wnd0 {
protected:
  virtual LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);
public:
  static LPCTSTR CLASS_NAME;
  CadWnd(HWND hwndParent);

};

}