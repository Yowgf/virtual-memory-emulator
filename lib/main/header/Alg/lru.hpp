//===----------------------------------------------------------===//
// Alg module
//
// File purpose: ~lru~ class declaration.
//===----------------------------------------------------------===//

#ifndef ALG_LRU_H
#define ALG_LRU_H

#include "Alg/emulator.hpp"

namespace Alg {

class lru : public emulator {
public:
  virtual void run();
};

}

#endif
