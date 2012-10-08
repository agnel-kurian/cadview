#include "stdafx.h"

#include "Utility.h"

namespace App0 {

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


}