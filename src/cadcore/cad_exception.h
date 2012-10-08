#ifndef CAD_EXCEPTION_H_INCLUDED
#define CAD_EXCEPTION_H_INCLUDED

#include <string>

namespace cad_core {

using std::string;

class cad_exception {
  string msg;

public:
  cad_exception(const string& msg) : msg(msg) {}
  virtual ~cad_exception(void) {}

  string& message() { return msg; }
};

}

#endif