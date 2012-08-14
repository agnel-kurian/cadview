#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <string>
#include <cstdlib>
#include <cassert>
#include "cad_primitives.h"

#include <boost/regex.hpp>

namespace cad_core {
  using std::string;
  using boost::regex;
  using boost::smatch;

  const regex re("(-?(?:\\d+|\\d*.\\d+)),(-?(?:\\d+|\\d*.\\d+))");
  template<typename T> bool parse_point_2d(const string& s, point_2d<T>& p){
    smatch matches;

    if(!regex_match(s, matches, re))
      return false;

    assert(matches.size() == 3);
    p.x = atof(matches.str(1).c_str());
    p.y = atof(matches.str(2).c_str());
    return true;
  }
}

#endif // UTIL_H_INCLUDED
