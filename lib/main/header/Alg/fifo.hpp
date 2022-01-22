//===----------------------------------------------------------===//
// Alg module
//
// File purpose: ~fifo~ class declaration.
//===----------------------------------------------------------===//

#ifndef ALG_FIFO_H
#define ALG_FIFO_H

#include "Alg/emulator.hpp"

namespace Alg {

class fifo : public emulator {
public:
  virtual void run();
};

}

#endif
