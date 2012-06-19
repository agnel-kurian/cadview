#ifndef CAD_GUI_VIEW_H_INCLUDED
#define CAD_GUI_VIEW_H_INCLUDED

#include "cad_document.h"
#include "cad_gui_view_input.h"
#include "cad_cmd.h"
#include "cad_polyline_cmd.h"
#include "cad_select_cmd.h"

#include <cassert>
#include <cstdio>

namespace cad_core {

template <typename T, typename U> class cad_gui_view {

  T translate_x;
  T translate_y;
  T scale;
  bool is_panning;
  point_2d<T> pan_start;

  U& gui;

  vector< cad_cmd<T, U> > commands;

public:
  typedef typename U::graphics_type graphics_type;
  typedef typename U::graphics_type::matrix_type matrix_type;
  cad_document<T>& document;

  cad_cmd<T, U> *current_cmd;

  cad_polyline_cmd<T, U> polyline_cmd;
  cad_select_cmd<T, U> select_cmd;
  cad_gui_view_input<T, U> *input;

  cad_gui_view(cad_document<T>& document, U& gui) :
    translate_x(T(0.0)), translate_y(T(0.0)), scale(T(1.0)), is_panning(false),
    pan_start(T(0.0), T(0.0)), gui(gui), document(document), current_cmd(0),
    polyline_cmd(*this), select_cmd(*this), input(0) {
  }

  bool get_point(point_2d<T>& point){
    assert(this->input == 0);
    cad_gui_view_input<T, U> input1(*this);

    input1.wait();

    if(input1.is_cancelled())
      return false;

    point = input1.get_point();
    return true;
  }

  void paint(){

    graphics_type graphics(gui);
    graphics.begin_paint(scale, translate_x, translate_y);

    const vector< polyline_2d<T> >& lines =
      document.get_polylines();

    for(int i = 0, n = lines.size(); i < n; ++i){

      const vector< point_2d<T> >& points = lines[i].points;
      const point_2d<T>& p0 = points[0];
      graphics.move_to(p0.x, p0.y);
      for(int ipoint = 1, npoint = points.size();
        ipoint < npoint; ++ipoint){

        const point_2d<T>& pi = points[ipoint];
        graphics.line_to(pi.x, pi.y);

      }
    }

    if(current_cmd != 0)
      current_cmd->paint(graphics);

    graphics.end_paint();
  }

  void run_cmd(cad_cmd<T, U>& cmd){
    current_cmd = &cmd;
    cmd.run();
    current_cmd = 0;
  }

  void run_polyline_cmd(){
    run_cmd(polyline_cmd);
  }

  void run_select_cmd(){
    run_cmd(select_cmd);
  }

  //  mouse move, mouse down, mouse up, mouse wheel
  void mouse_move(int x, int y){
    /*
    get point handler will not do anything here ...yet
    even if snap is on, current_cmd is expected to display the glyph
    we might need to display co-ordinates in status bar...
    */
    if(is_panning){
      T dx = (T)x, dy = (T)y;
      graphics_type graphics(gui);
      graphics.set_matrix(scale, translate_x, translate_y);
      graphics.device_to_user(&dx, &dy);
      translate_x += dx - pan_start.x;
      translate_y += dy - pan_start.y;
      gui.invalidate();
    }
    else if(current_cmd != 0){
      current_cmd->mouse_move(x, y);
      return;
    }

  /*
    otherwise...

      find object under cursor and highlight?

  */

  }

  void mouse_down(Mouse_button button, int x, int y){
    /*
      get_point need not do anything here; we collect x,y on mouse_up
      current_cmd need not do anything here yet
    */
    if(button == Mouse_button_Middle){
      is_panning = true;
      pan_start.x = (T)x;
      pan_start.y = (T)y;
      graphics_type graphics(gui);
      graphics.set_matrix(scale, translate_x, translate_y);
      graphics.device_to_user(&pan_start.x, &pan_start.y);
    }
  }

  void mouse_up(Mouse_button button, int x, int y){

    if(button == Mouse_button_Left){
      if(is_panning)
        return;

      if(input != 0){
        input->left_mouse_up(x, y);
        return;
      }

    }
    else if(button == Mouse_button_Middle){
      is_panning = false;
    }
    else if(button == Mouse_button_Right){

      if(input != 0){
        input->right_mouse_up();
        return;
      }

      /*
      todo:
      if current_cmd != 0
        current_cmd->cancel();
        return;

      determine context menu depending on what is under the cursor?
      display a context menu
      */

    }
    else
      fprintf(stderr, "button %d\n", button);

  }

  void mouse_scroll(Mouse_scroll_direction direction,
    int x, int y){
    /*
    disable this when waiting for the mouse_up of a get_point or pan
    */
    matrix_type mx1;
    graphics_type::set_matrix(&mx1, scale, translate_x, translate_y);
    graphics_type::invert_matrix(&mx1);
    T x1 = x, y1 = y;
    graphics_type::transform_point(&mx1, &x1, &y1);

    if(direction == Mouse_scroll_direction_Up)
      scale *= 1.1;
    else if(direction == Mouse_scroll_direction_Down)
      scale /= 1.1;
    else
      assert(false);

    matrix_type mx2;
    graphics_type::set_matrix(&mx2, scale, translate_x, translate_y);
    graphics_type::invert_matrix(&mx2);
    T x2 = x, y2 = y;
    graphics_type::transform_point(&mx2, &x2, &y2);

    translate_x += x2 - x1;
    translate_y += y2 - y1;

    gui.invalidate();
  }

  U& get_gui(){
    return gui;
  }

  void device_to_user(point_2d<T>& point){
    matrix_type mx;
    graphics_type::set_matrix(&mx, scale, translate_x, translate_y);
    graphics_type::invert_matrix(&mx);
    graphics_type::transform_point(&mx, &point.x, &point.y);
  }

  cad_gui_view_input<T, U> *get_input(){
    return input;
  }

  void set_input(cad_gui_view_input<T, U> *input){
    assert((this->input == 0 && input != 0)
           || (input == 0 && this->input != 0));

    this->input = input;
  }

};

}

#endif // CAD_GUI_VIEW_H_INCLUDED
