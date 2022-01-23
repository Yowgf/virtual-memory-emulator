//===----------------------------------------------------------===//
// Alg module
//
// File purpose: ~emulator~ class declaration.
//===----------------------------------------------------------===//

#ifndef ALG_EMULATOR_H
#define ALG_EMULATOR_H

#include "Memory/vtable.hpp"
#include "Utils/defs.hpp"

#include <string>
#include <vector>

namespace Alg {

constexpr char READ_OP = 'R';
constexpr char WRITE_OP = 'W';

typedef struct {
  unsigned address;
  char type; // R (Read) or W (Write)
} memopT;

typedef std::vector<memopT> memopsT;

typedef struct {
  // How many pages were requested that were not in the vtable
  unsigned numPageFaults;
  // How many pages had to be written back to physical memory
  unsigned numPageWrites;
} statsT;

class emulator {
public:
  void configure(std::string filePath);

  virtual void run() = 0;

  template<typename compare>
  void processOperations(memopsT& memops, Memory::vtable<compare> vtable)
  {
    for (auto it = memops.begin(); it != memops.end(); it++) {
      Memory::vtableOpRespT resp;
      if (it->type == READ_OP) {
	resp = vtable.read(it->address);
      } else {
	resp = vtable.write(it->address);
      }
      handleVtableResponse<compare>(resp, vtable, it->address);
    }
  }
  
  template<typename compare>
  void handleVtableResponse(Memory::vtableOpRespT& resp, Memory::vtable<compare>& vtable, unsigned address)
  {
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

  void logStats();

protected:
  unsigned pageSize;
  unsigned memorySize;
  memopsT memops;
  statsT stats;

private:
  // Read file entries into local vector
  void decodeFile(std::string filePath);
};

}

#endif
