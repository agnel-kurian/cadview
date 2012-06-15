#ifndef CAD_SELECT_CMD_H_INCLUDED
#define CAD_SELECT_CMD_H_INCLUDED

#include "cad_document.h"

#include <cassert>
#include <cstdio>

namespace cad_core {

template <typename T, typename U> class cad_select_cmd
  : public cad_cmd<T, U> {

  cad_gui_view<T, U>& view;
  U& gui;

public:
  typedef typename U::graphics_type graphics_type;

  cad_select_cmd(cad_gui_view<T, U>& view) : view(view), gui(view.get_gui()) {
  }

  void paint(graphics_type& graphics){
  }

  //  mouse move, mouse down, mouse up, mouse wheel
  void mouse_move(int x, int y){
  }

  bool run(){
    //  for now, just ask user to select a point
    point_2d<T> p;
    return view.get_point(p);
  }

  //  todo: keyboard handling
};

}

#endif // CAD_SELECT_CMD_H_INCLUDED
