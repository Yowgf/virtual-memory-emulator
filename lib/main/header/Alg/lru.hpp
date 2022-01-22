//===----------------------------------------------------------===//
// Alg module
//
// File purpose: ~lru~ class declaration.
//===----------------------------------------------------------===//

#ifndef ALG_LRU_H
#define ALG_LRU_H

#include "Alg/emulator.hpp"

namespace Alg {

struct lruPageCompare {
  bool operator()(const Memory::pageT& p1, const Memory::pageT& p2) const {
    return p1.lastUsedAt > p2.lastUsedAt;
  }
};

class lru : public emulator {
public:
  lru(unsigned pageSize, unsigned memorySize, std::string filePath);

  virtual void run();
  virtual void processRead(unsigned address);
  virtual void processWrite(unsigned address);

private:
  Memory::vtable<lruPageCompare> vtable;
};

}

#endif
