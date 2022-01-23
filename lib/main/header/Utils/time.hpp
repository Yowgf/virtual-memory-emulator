//===----------------------------------------------------------===//
// Utils module
//
// File purpose: useful time functions. Notably, a macro to time the
// execution time of some expression.
//===----------------------------------------------------------===//

#ifndef TIME_H
#define TIME_H

#include "Utils/defs.hpp"

#include <chrono>

#ifdef MEASURE_TIME
#define TIME_EXECUTION(clkVar, expr) {                         \
  auto t1 = std::chrono::high_resolution_clock::now();         \
  (expr);                                                      \
  auto t2 = std::chrono::high_resolution_clock::now();         \
  clkVar = t2 - t1;     \
  }
#else
#define TIME_EXECUTION(clkVar, expr) (expr);
#endif

typedef std::chrono::duration<double> clockT;

namespace Utils {

class time {
public:
  static long int now_nanoseconds()
  {
    return std::chrono::time_point_cast<std::chrono::nanoseconds>
      (std::chrono::high_resolution_clock::now()).time_since_epoch().count();
  }
};

}

#endif // #ifdef TIME_H
