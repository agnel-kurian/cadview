#ifndef CAD_POLYLINE_CMD_H_INCLUDED
#define CAD_POLYLINE_CMD_H_INCLUDED

#include "cad_document.h"

#include <cassert>
#include <cstdio>

namespace cad_core {

template <typename T, typename U> class cad_polyline_cmd
  : public cad_cmd<T, U> {

  cad_gui_view<T, U>& view;
  U& gui;

  polyline_2d<T> new_polyline;

public:
  typedef typename U::graphics_type graphics_type;

  cad_polyline_cmd(cad_gui_view<T, U>& view) : view(view), gui(view.get_gui()) {
  }

  void paint(graphics_type& graphics){

    vector< point_2d<T> >& points = new_polyline.points;

    if(points.size() > 0){

      graphics.draw_polyline(new_polyline);
      point_2d<T>& plast = points.back();
      graphics.move_to(plast.x, plast.y);
      int x, y;
      gui.get_mouse_position(&x, &y);
      T dx = (T)x, dy = (T)y;
      graphics.device_to_user(&dx, &dy);
      graphics.line_to(dx, dy);

    }

  }

  //  mouse move, mouse down, mouse up, mouse wheel
  void mouse_move(int x, int y){

    if(new_polyline.points.size() > 0)
      gui.invalidate();

  }

  bool run(){
    new_polyline.points.clear();

    //  todo
    //  prompt for a point
    //  if cancelled, end command
    point_2d<T> p;
    while(view.get_point(p)){
      new_polyline.points.push_back(p);
    }

    gui.invalidate();

    if(new_polyline.points.size() > 1)
      view.document.add_polyline(new_polyline);
    return true;
  }

  //  todo: keyboard handling
};

}

#endif // CAD_POLYLINE_CMD_H_INCLUDED
