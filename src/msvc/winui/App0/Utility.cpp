#include "stdafx.h"

#include "Utility.h"
#include "app0_exception.h"

namespace App0 {

TCHAR* ERR_GetDC_FAILED = _T("GetDC failed");


void LogLastError(){
  _com_error error(GetLastError());
  LPCTSTR errorText = error.ErrorMessage();
  ::OutputDebugString(boost::str(tformat(_T("%s\n")) % errorText).c_str());
}

HFONT GetDefaultFont(){
  NONCLIENTMETRICS ncm;
  ncm.cbSize = sizeof(ncm);

  if(IsVistaOrLater())
    ncm.cbSize -= sizeof(ncm.iPaddedBorderWidth);

  if(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0) == 0){

    LogLastError();
    return 0;
  }

  return ::CreateFontIndirect(&ncm.lfMessageFont);
}

bool IsVistaOrLater(){
  OSVERSIONINFO osver;
  ::ZeroMemory(&osver, sizeof(osver));
  osver.dwOSVersionInfoSize = sizeof(osver);
  ::GetVersionEx(&osver);

  return osver.dwMajorVersion >= 6;
}

TmpDC::TmpDC(HWND hwnd) : hwnd(hwnd) {
  hdc = ::GetDC(hwnd);
  if(hdc == 0)
    throw app0_exception(ERR_GetDC_FAILED);
}

TmpDC::operator HDC(){
  return hdc;
}

TmpDC::~TmpDC(){
  ::ReleaseDC(hwnd, hdc);
}

int GetTextHeight(HWND hwnd){
  TmpDC dc(hwnd);

  TEXTMETRIC tm;
  if(!GetTextMetrics(dc, &tm))
    return 0;

  ::ReleaseDC(hwnd, dc);

  return tm.tmExternalLeading + tm.tmHeight;
}

InitGdiplus::InitGdiplus(){
  Gdiplus::GdiplusStartup(&token, &sin, &sout);
}

InitGdiplus::~InitGdiplus(){
  Gdiplus::GdiplusShutdown(token);
}

}