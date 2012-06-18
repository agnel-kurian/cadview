#ifndef CAD_GUI_VIEW_INPUT_H_INCLUDED
#define CAD_GUI_VIEW_INPUT_H_INCLUDED

#include <cassert>

namespace cad_core {

template <typename T, typename U> class cad_gui_view;

enum Input_mode {
  Input_mode_Get_point,
  Input_mode_Get_string,
  Input_mode_Get_point_or_string
};

template <typename T, typename U> class cad_gui_view_input {
  typedef typename U::graphics_type graphics_type;
  typedef typename U::graphics_type::matrix_type matrix_type;

  bool cancelled;
  bool is_point;
  point_2d<T> point_input;
//  string string_input;

  cad_gui_view<T, U>& view;
  U& gui;

public:
  cad_gui_view_input(cad_gui_view<T, U>& view) : cancelled(false), view(view), gui(view.get_gui()) {
    assert(view.get_input() == 0);
    view.set_input(this);
  }

  void left_mouse_up(int x, int y){
    point_input.x = (T)x;
    point_input.y = (T)y;
    view.device_to_user(point_input);

    gui.exit_event_loop();
  }

  void right_mouse_up(){
    cancelled = true;
    gui.exit_event_loop();
  }

  bool is_cancelled(){
    return cancelled;
  }

  point_2d<T> get_point(){
    return point_input;
  }

  void wait(){
    gui.run_event_loop();
  }

  ~cad_gui_view_input(){
    view.set_input(0);
  }
};

}

#endif // CAD_GUI_VIEW_INPUT_H_INCLUDED
