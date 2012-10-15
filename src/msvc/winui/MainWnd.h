#ifndef MAINWND_INCLUDED
#define MAINWND_INCLUDED

#include "App0/Wnd0.h"

#include "cad_gui_view.h"

using App0::Wnd0;

namespace cadwin {

class LogWnd;
class CadWnd;
class CmdLineWnd;
class MainWnd;

class MainWnd : public Wnd0 {
  CmdLineWnd* cl;
  LogWnd* log;
  CadWnd* cad;

protected:
  LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

public:
  static const TCHAR *CLASS_NAME;
  MainWnd();
  void OnPaint(HWND);
  void OnDestroy(HWND);
  void OnClose(HWND);
  void OnSize(HWND, UINT state, int cx, int cy);
  void OnCommand(HWND, int id, HWND hwndCtl, UINT codeNotify);
  void OnMouseWheel(HWND hwnd, int xPos, int yPos, int zDelta, UINT fwKeys);


  virtual ~MainWnd();

  void SetCmdLine(CmdLineWnd* cl);
  void SetLog(LogWnd* log);
  void SetCad(CadWnd* cad);

  CadWnd& GetCad(){ return *cad; }

};

}

#endif