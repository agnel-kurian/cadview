#include "stdafx.h"
#include "CmdLineWnd.h"
#include "MainWnd.h"
#include "CadWnd.h"
#include "App0/Utility.h"

using App0::TmpDC;

namespace cadwin {

CmdLineWnd::CmdLineWnd(MainWnd &parent) : Wnd0(_T("EDIT"), 0UL, _T(""),
  WS_CHILD | WS_BORDER | WS_VISIBLE,
  300, 0, 300, 200, parent), parent(parent) {

  hfont = App0::GetDefaultFont();
  if(hfont != 0)
    ::SendMessage(GetHandle(), WM_SETFONT, (WPARAM)hfont, MAKELPARAM(FALSE, 0));

  HWND hwnd = GetHandle();
  int height = App0::GetTextHeight(hwnd) + 2;
  ::MoveWindow(hwnd, 0, 0, 300, height, FALSE);
}

LRESULT CmdLineWnd::WndProc(UINT msg, WPARAM wParam, LPARAM lParam){
  HWND hwnd = GetHandle();
  switch(msg){
    HANDLE_MSG(hwnd, WM_KEYUP, OnKey);
  }

  WNDPROC baseWndProc = GetBaseWndProc();
  return baseWndProc(GetHandle(), msg, wParam, lParam);
}

CmdLineWnd::~CmdLineWnd(){
  ::DeleteObject(hfont);
}

void CmdLineWnd::OnKey(HWND, UINT vk, BOOL fDown, int cRepeat, UINT flags){
  if(fDown)
    return;

  if(vk == VK_ESCAPE){
    parent.GetCad().GetView()->cancel_input();
  }
  else if(vk == VK_RETURN){
      
    int length = ::Edit_GetTextLength(*this);
    TCHAR *buffer = (TCHAR*) ::malloc(sizeof(TCHAR) * (length + 1));
    if(!buffer){
      ::OutputDebugString(_T("Out of memory.\n"));
      return;
    }

    ::Edit_GetText(*this, buffer, length + 1);

#ifdef UNICODE
    char *cbuffer = new char[length + 1];
    size_t nconv;
    wcstombs_s(&nconv, cbuffer, length + 1,
      buffer, sizeof(TCHAR) * (length + 1));
#else
    char *cbuffer = buffer;
#endif

    std::string input(cbuffer);
    parent.GetCad().GetView()->set_input_string(input);
    ::Edit_SetText(*this, _T(""));
    ::free(buffer);

#ifdef UNICODE
    delete[] cbuffer;
#endif
  }
}

}
