//===----------------------------------------------------------===//
// Alg module
//
// File purpose: implementation of class ~lru~. See header file for
// more detail.
//===----------------------------------------------------------===//

#include "Alg/lru.hpp"
#include "Utils/defs.hpp"

namespace Alg {

lru::lru(unsigned pageSize, unsigned memorySize, std::string filePath) :
  vtable(pageSize, memorySize)
{
  BOOST_LOG_TRIVIAL(info) << "(lru) initializing lru (pageSize="
			  << pageSize << " memorySize=" << memorySize << ")";
  configure(filePath);
}

void lru::run()
{
  processOperations<lruPageCompare>(memops, vtable);
}

}
