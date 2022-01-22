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
  fifo(unsigned pageSize, unsigned memorySize, std::string filePath);
  virtual void run();
  virtual void processRead(unsigned address);
  virtual void processWrite(unsigned address);
};

}

#endif
