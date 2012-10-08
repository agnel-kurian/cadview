#ifndef MAINWND_INCLUDED
#define MAINWND_INCLUDED

#include "App0/Wnd0.h"

#include "cad_gui_view.h"

using App0::Wnd0;

namespace cadwin {

class MainWnd : public Wnd0 {
  CmdLineWnd* cl;
  LogWnd* log;
  CadWnd* cad;

protected:
  LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

public:
  static const TCHAR *CLASS_NAME;
  MainWnd();
  void OnWmPaint(HWND);
  void OnWmDestroy(HWND);
  void OnWmClose(HWND);
  void OnWmSize(HWND, UINT state, int cx, int cy);
  void OnWmCommand(HWND, int id, HWND hwndCtl, UINT codeNotify);

  virtual ~MainWnd();

  void SetCmdLine(CmdLineWnd* cl);
  void SetLog(LogWnd* log);
  void SetCad(CadWnd* cad);

  CadWnd* GetCad(){ return cad; }

};

}

#endif