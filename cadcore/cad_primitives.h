#ifndef CAD_PRIMITIVES_H_INCLUDED
#define CAD_PRIMITIVES_H_INCLUDED

#include <vector>

namespace cad_core {

using std::vector;

struct screen_point {
  int x;
  int y;

  screen_point() : x(0), y(0) {}
  screen_point(int x, int y) : x(x), y(y) {}
};

template <typename T> struct point_2d {
  T x;
  T y;

  inline point_2d(T x = T(0.0), T y = T(0.0)) : x(x), y(y) {
  }

  inline point_2d(const point_2d<T>& p) : x(p.x), y(p.y) {
  }
};

template <typename T> struct line_2d {
  point_2d<T> start;
  point_2d<T> end;

  inline line_2d() : start(0.0, 0.0), end(1.0, 0.0) {
  }

  inline line_2d(point_2d<T> start, point_2d<T> end) : start(start), end(end) {
  }

  inline line_2d(const line_2d<T>& l) : start(l.start), end(l.end) {
  }
};

template <typename T> struct polyline_2d {
  vector< point_2d<T> > points;
};

template <typename T, typename U> struct cad_entity {
  typedef typename U::graphics_type graphics_type;
  virtual void paint(graphics_type& graphics) = 0;
};

template <typename T, typename U> struct cad_polyline_2d
  : public cad_entity<T, U> {

  typedef typename U::graphics_type graphics_type;

  vector< point_2d<T> > points;

  void paint(graphics_type& graphics) const {
    const vector< point_2d<T> >& pts = points;
    const point_2d<T>& p0 = pts[0];
    graphics.move_to(p0.x, p0.y);
    for(int ipoint = 1, npoint = pts.size();
      ipoint < npoint; ++ipoint){

      const point_2d<T>& pi = pts[ipoint];
      graphics.line_to(pi.x, pi.y);

    }
  }
};

template <typename T, typename U> struct cad_line_2d : public cad_entity<T, U> {
  typedef typename U::graphics_type graphics_type;
  point_2d<T> start;
  point_2d<T> end;

  void paint(graphics_type& graphics) const {
    graphics.move_to(start);
    graphics.line_to(end);
  }
};

}

#endif // CAD_PRIMITIVES_H_INCLUDED
