//===----------------------------------------------------------===//
// Alg module
//
// File purpose: ~newalg~ class declaration.
//===----------------------------------------------------------===//

#ifndef ALG_NEWALG_H
#define ALG_NEWALG_H

#include "Alg/emulator.hpp"

namespace Alg {

class newalg : public emulator {
public:
  newalg(unsigned pageSize, unsigned memorySize, std::string filePath);
  virtual void run();
};

}

#endif
