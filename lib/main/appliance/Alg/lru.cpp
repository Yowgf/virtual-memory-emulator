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
  processOperations(memops);
}

void lru::processRead(unsigned address)
{
  Memory::vtableOpRespT resp = vtable.read(address);
  if (!resp.wasPageFound) {
    stats.numPageFaults++;
    if (vtable.full()) {
      bool wasDirty = vtable.replaceTopPage(address);
      if (wasDirty) {
	stats.numPageWrites++;
      }
    } else {
      vtable.insertNewPage(address);
    }
  }
}

void lru::processWrite(unsigned address)
{
  Memory::vtableOpRespT resp = vtable.write(address);
  if (!resp.wasPageFound) {
    stats.numPageFaults++;
    if (vtable.full()) {
      BOOST_LOG_TRIVIAL(debug) << "vtable is full";
      bool wasDirty = vtable.replaceTopPage(address);
      if (wasDirty) {
	stats.numPageWrites++;
      }
    } else {
      vtable.insertNewPage(address);
    }
  }
}

}
