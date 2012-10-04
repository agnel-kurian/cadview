#include "cad_primitives.h"
#include "cad_document.h"
#include "cad_gui_view.h"

namespace cad_core {

template struct point_2d<float>;
template struct line_2d<float>;
template struct polyline_2d<float>;
template class cad_document<float>;

template struct point_2d<double>;
template struct line_2d<double>;
template struct polyline_2d<double>;
template class cad_document<double>;

}
