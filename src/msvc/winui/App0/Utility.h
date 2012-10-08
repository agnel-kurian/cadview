#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED

namespace App0 {

  extern TCHAR* ERR_GetDC_FAILED;

  void LogLastError();
  bool IsVistaOrLater();
  HFONT GetDefaultFont();

class TmpDC {
  HDC hdc;
  HWND hwnd;
public:
  TmpDC(HWND hwnd);
  operator HDC();
  ~TmpDC();
};

using Gdiplus::GdiplusStartupInput;
using Gdiplus::GdiplusStartupOutput;

class InitGdiplus {
  GdiplusStartupInput sin;
  GdiplusStartupOutput sout;
  ULONG_PTR token;
public:
  InitGdiplus();
  ~InitGdiplus();
};

int GetTextHeight(HWND hwnd);

}

#endif