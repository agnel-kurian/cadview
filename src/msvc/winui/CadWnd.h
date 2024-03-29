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

  void OnPaint(HWND);
  void OnMouseMove(HWND, int x, int y, UINT keyFlags);
  void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
  void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
  void OnMButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
  void OnMButtonUp(HWND hwnd, int x, int y, UINT flags);
  void OnRButtonUp(HWND hwnd, int x, int y, UINT flags);

protected:
  virtual LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

private:
  view_type* view;

};

}