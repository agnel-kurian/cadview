#ifndef CAD_WND_INCLUDED
#define CAD_WND_INCLUDED

#include "App0/Wnd0.h"
#include "cad_gui_view.h"

using App0::Wnd0;

namespace cadwin {

class MainWnd : public Wnd0 {
protected:
  LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);
public:
  static const TCHAR *CLASS_NAME;
  MainWnd();
  void OnWmPaint(HWND);
  void OnWmDestroy(HWND);
  void OnWmClose(HWND);
};

}

#endif