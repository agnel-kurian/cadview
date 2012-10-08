#pragma once

#include "App0/Wnd0.h"
#include "cad_gui_view.h"
#include "cad_win_adaptor.h"

using App0::Wnd0;

namespace cadwin {

class CadWnd : public Wnd0 {
public:
  typedef cad_core::cad_gui_view<double,
    cad_win::cad_win_adaptor<double> > view_type;

  static LPCTSTR CLASS_NAME;
  CadWnd(HWND hwndParent);
  void SetView(view_type* view);
  view_type* GetView(){ return view; }

  void OnWmPaint(HWND);
  void OnWmMouseMove(HWND, int x, int y, UINT keyFlags);
  void OnWmLButtonDown(HWND hwnd, BOOL fDoubleClick,
    int x, int y, UINT keyFlags);
  void OnWmLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
  void OnWmMButtonDown(HWND hwnd, BOOL fDoubleClick,
    int x, int y, UINT keyFlags);
  void OnWmMButtonUp(HWND hwnd, int x, int y, UINT flags);
  void OnWmRButtonUp(HWND hwnd, int x, int y, UINT flags);
  void OnWmMouseWheel(HWND hwnd, int xPos, int yPos,
    int zDelta, UINT fwKeys);

protected:
  virtual LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

private:
  view_type* view;

};

}