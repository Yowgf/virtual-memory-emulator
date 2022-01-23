//===----------------------------------------------------------===//
// Alg module
//
// File purpose: ~fifo~ class declaration.
//===----------------------------------------------------------===//

#ifndef ALG_FIFO_H
#define ALG_FIFO_H

#include "Alg/emulator.hpp"

namespace Alg {

struct fifoPageCompare {
  bool operator()(const Memory::pageT& p1, const Memory::pageT& p2) const {
    return p1.createdAt < p2.createdAt;
  }
};

class fifo : public emulator {
public:
  fifo(unsigned pageSize, unsigned memorySize, std::string filePath);
  virtual void run();

private:
  Memory::vtable<fifoPageCompare> vtable;
};

}

#endif
