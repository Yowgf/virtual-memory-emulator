//===----------------------------------------------------------===//
// Alg module
//
// File purpose: implementation of class ~newalg~. See header file for
// more detail.
//===----------------------------------------------------------===//

#include "Alg/newalg.hpp"

namespace Alg {

newalg::newalg(unsigned pageSize, unsigned memorySize, std::string filePath) :
  emulator(), vtable(pageSize, memorySize)
{}

void newalg::run()
{}

}
