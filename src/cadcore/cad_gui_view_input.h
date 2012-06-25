#ifndef CAD_GUI_VIEW_INPUT_H_INCLUDED
#define CAD_GUI_VIEW_INPUT_H_INCLUDED

#include <cassert>
#include <string>

#include "util.h"

namespace cad_core {

using std::string;
template <typename T, typename U> class cad_gui_view;

enum Input_type {
  Input_type_None = 0,
  Input_type_Point = 1,
  Input_type_String = 2,
  Input_type_Option = 4
};

template <typename T, typename U> class cad_gui_view_input {
  typedef typename U::graphics_type graphics_type;
  typedef typename U::graphics_type::matrix_type matrix_type;

  bool cancelled;
  bool is_point;
  point_2d<T> point_input;
  string string_input;

  Input_type expected;
  Input_type entered;
  cad_gui_view<T, U>& view;
  U& gui;

public:
  cad_gui_view_input(cad_gui_view<T, U>& view, Input_type expected)
    : cancelled(false), expected(expected), entered(Input_type_None),
      view(view), gui(view.get_gui()) {
    assert(expected != Input_type_None);
    assert(view.get_input() == 0);
    view.set_input(this);

  }

  Input_type get_input_type(){
    return entered;
  }

  void left_mouse_up(int x, int y){
    if((expected & Input_type_Point) != 0){
      entered = Input_type_Point;

      point_input.x = (T)x;
      point_input.y = (T)y;
      view.device_to_user(point_input);

      gui.exit_event_loop();
    }
  }

  void right_mouse_up(){
    cancel_input();
  }

  void cancel_input(){
    cancelled = true;
    gui.exit_event_loop();
  }

  //  set_input_string
  //  sets input as a string. if point is expected, we try to parse the string

  bool set_input_string(const string& input, string &err){
    string_input = input;

    //  try to parse as a point
    if((expected & Input_type_Point) != 0){
      point_2d<T> p;
      if(!parse_point_2d(input, p)){
        //  if no other input type is expected, we abort
        if((expected & ~Input_type_Point) == 0){
          err = "Invalid point.";
          return false;
        }
      }

      entered = Input_type_Point;

      point_input.x = p.x;
      point_input.y = p.y;

      gui.exit_event_loop();
      return true;
    }

    //  just save the string
    if((expected & Input_type_String) != 0){
      entered = Input_type_String;
      gui.exit_event_loop();
      return true;
    }

    return false;
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
