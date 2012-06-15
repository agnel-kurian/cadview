#ifndef CAD_CMD_H_INCLUDED
#define CAD_CMD_H_INCLUDED

#include "cad_document.h"

#include <cassert>
#include <cstdio>
#include <string>

namespace cad_core {

enum Mouse_scroll_direction {
  Mouse_scroll_direction_None,
  Mouse_scroll_direction_Up,
  Mouse_scroll_direction_Down
};

enum Mouse_button {
  Mouse_button_None,
  Mouse_button_Left,
  Mouse_button_Middle,
  Mouse_button_Right
};

template <typename T, typename U> class cad_gui_view;
using std::string;

template <typename T, typename U> class cad_cmd {
protected:
  typedef typename U::graphics_type graphics_type;
public:
  virtual void paint(graphics_type& graphics) = 0;

  virtual void mouse_move(int x, int y) = 0;

  virtual bool run() = 0;

};

}

#endif // CAD_CMD_H_INCLUDED
