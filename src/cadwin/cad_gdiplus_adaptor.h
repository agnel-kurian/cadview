#ifndef GDIPLUS_ADAPTOR_INCLUDED
#define GDIPLUS_ADAPTOR_INCLUDED

#include "cad_primitives.h"
#include <gdiplus.h>
#include <vector>

namespace cad_win {

using cad_core::point_2d;
using cad_core::polyline_2d;

template<typename T> class cad_win_adaptor;

using Gdiplus::Matrix;
using Gdiplus::Graphics;
using Gdiplus::Color;
using Gdiplus::Pen;
using Gdiplus::PointF;
using Gdiplus::GraphicsState;
using Gdiplus::REAL;

using std::vector;

template<typename T> class cad_gdiplus_adaptor {
  Graphics gr;
  GraphicsState state;
  Pen p0;
  point_2d<T> pen_pos;
public:
  typedef Matrix matrix_type;

  cad_gdiplus_adaptor(HDC dc) : gr(dc), p0(Color(0, 0, 0), 0.0f) {
    state = gr.Save();
  }

  cad_gdiplus_adaptor(cad_win_adaptor<T>& gui) : p0(Color(0, 0, 0), 0.0f),
    gr(gui.get_hwnd()) {
  }

  void set_matrix(T scale, T translate_x, T translate_y){
    Matrix mx;
    mx.Scale((REAL)scale, (REAL)scale);
    mx.Translate((REAL)translate_x, (REAL)translate_y);
    gr.SetTransform(&mx);
  }

  void begin_paint(T scale, T translate_x, T translate_y){
    set_matrix(scale, translate_x, translate_y);
  }

  void move_to(const point_2d<T>& p){
    pen_pos = p;
  }

  void move_to(const T x, const T y){
    pen_pos = point_2d<T>(x, y);
  }

  void line_to(const T x, const T y){
    gr.DrawLine(&p0, (REAL) pen_pos.x, (REAL) pen_pos.y,
      (REAL) x, (REAL) y);
    pen_pos.x = x;
    pen_pos.y = y;
  }

  void draw_polyline(const polyline_2d<T>& polyline){
    const std::vector< point_2d<T> >& points = polyline.points;
    vector<PointF> pts;
    int n = points.size();
    for(int i = 0; i < n; ++i){
      point_2d<T> point = points[i];
      pts.push_back(PointF((float)point.x, (float)point.y));
    }

    gr.DrawLines(&p0, &pts[0], n);
  }

  void device_to_user(T *x, T *y){
    PointF p((float) *x, (float) *y);
    matrix_type mx;
    gr.GetTransform(&mx);
    mx.Invert();
    mx.TransformPoints(&p);
    *x = (T) p.X;
    *y = (T) p.Y;
  }

  static void set_matrix(matrix_type *mx, T scale,
    T translate_x, T translate_y){

    mx->Reset();
    mx->Scale((float) scale, (float) scale);
    mx->Translate((float) translate_x, (float) translate_y);

  }

  static void invert_matrix(matrix_type *mx){
    mx->Invert();
  }

  static void transform_point(const matrix_type *mx, T* x, T* y){
    PointF p((float) *x, (float) *y);
    mx->TransformPoints(&p, 1);
    *x = (T) p.X;
    *y = (T) p.Y;
  }

  static void transform_point(const matrix_type *mx, point_2d<T>* p){
    transform_point(mx, &(p->x), &(p->y));
  }

  void end_paint(){
  }

};

}

#endif  //  GDIPLUS_ADAPTOR_INCLUDED