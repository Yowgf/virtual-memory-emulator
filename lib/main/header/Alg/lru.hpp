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
    // We want the page with minimum lastUsedAt
    return p1.lastUsedAt > p2.lastUsedAt;
  }
};

class lru : public emulator {
public:
  explicit lru(unsigned pageSize, unsigned memorySize, std::string filePath);
  ~lru() = default;
  virtual void run();

private:
  Memory::vtable<lruPageCompare> vtable;
};

}

#endif
