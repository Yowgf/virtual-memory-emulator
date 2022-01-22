//===----------------------------------------------------------===//
// Alg module
//
// File purpose: ~emulator~ class declaration.
//===----------------------------------------------------------===//

#ifndef ALG_EMULATOR_H
#define ALG_EMULATOR_H

#include "Memory/vtable.hpp"

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
  virtual void processRead(unsigned address) = 0;
  virtual void processWrite(unsigned address) = 0;

  void processOperations(memopsT& memops);
  void logStats(); // TODO

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
