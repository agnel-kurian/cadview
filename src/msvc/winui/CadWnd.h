#ifndef CAD_WND_INCLUDED
#define CAD_WND_INCLUDED

#include "App0/BaseWnd.h"
#include "cad_gui_view.h"

using App0::BaseWnd;

namespace cadwin {

class CadWnd : public BaseWnd {
public:
  CadWnd();
  void OnWmPaint(HWND hwnd);
};

}

#endif