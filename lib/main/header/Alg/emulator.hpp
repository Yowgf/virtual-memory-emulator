//===----------------------------------------------------------===//
// Alg module
//
// File purpose: ~emulator~ class declaration.
//===----------------------------------------------------------===//

#ifndef ALG_EMULATOR_H
#define ALG_EMULATOR_H

#include <string>
#include <vector>

namespace Alg {

typedef struct {
  unsigned address;
  char type; // R (Read) or W (Write)
} memop;

class emulator {
public:
  void configure(int pageSize, int memorySize, std::string filePath);

  virtual void run() = 0;

protected:
  int pageSize;
  int memorySize;
  std::vector<memop> memops;

private:
  // Read file entries into local vector
  void decodeFile(std::string filePath);
};

}

#endif
