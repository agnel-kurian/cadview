#pragma once

#include "App0/Wnd0.h"

using App0::Wnd0;

namespace cadwin {

class MainWnd;

class CmdLineWnd : public Wnd0 {
  HFONT hfont;
  MainWnd &parent;
protected:
  virtual LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

  void OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);

public:
  CmdLineWnd(MainWnd &parent);
  ~CmdLineWnd();
};

}