//===----------------------------------------------------------===//
// Alg module
//
// File purpose: ~newalg~ class declaration.
//===----------------------------------------------------------===//

#ifndef ALG_NEWALG_H
#define ALG_NEWALG_H

#include "Alg/emulator.hpp"
#include "Utils/defs.hpp"

namespace Alg {

struct newalgPageCompare {
  bool operator()(const Memory::pageT& p1, const Memory::pageT& p2) const {
    // We want page with minimum historyUses to be replaced
    return p1.historyUses > p2.historyUses;
  }
};

class newalg : public emulator {
public:
  explicit newalg(unsigned pageSize, unsigned memorySize, std::string filePath);
  ~newalg() = default;
  virtual void run();

private:
  Memory::vtable<newalgPageCompare> vtable;
};

}

#endif
