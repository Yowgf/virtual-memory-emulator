//===----------------------------------------------------------===//
// Alg module
//
// File purpose: implementation of class ~fifo~. See header file for
// more detail.
//===----------------------------------------------------------===//

#include "Alg/fifo.hpp"

namespace Alg {

fifo::fifo(unsigned pageSize, unsigned memorySize, std::string filePath) :
  emulator(), vtable(pageSize, memorySize)
{
  BOOST_LOG_TRIVIAL(info) << "(fifo) initializing fifo (pageSize="
			  << pageSize << " memorySize=" << memorySize << ")";
  configure(filePath);
}

void fifo::run()
{
  processOperations<fifoPageCompare>(memops, vtable);
}

}
