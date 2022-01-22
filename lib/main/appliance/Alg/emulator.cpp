//===----------------------------------------------------------===//
// Alg module
//
// File purpose: implementation of class ~emulator~. See header file for
// more detail.
//===----------------------------------------------------------===//

#include "Alg/emulator.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace Alg {

void emulator::configure(std::string filePath)
{
  decodeFile(filePath);
}

void emulator::decodeFile(std::string filePath)
{
  auto file = std::ifstream{filePath, std::ifstream::in};
  unsigned i = 0;
  while (file.good()) {
    auto op = memopT{};
    file >> std::hex >> op.address >> op.type;
    memops.push_back(op);
    i++;
  }
  // Something went wrong while reading file
  if (!file.eof()) {
    char buffer[128];
    sprintf(buffer, "Error while decoding file for emulator. "	\
	    "State of the stream: %d %d %d %d",
	    file.good(), file.eof(), file.fail(), file.bad());
    throw std::runtime_error(buffer);
  }
}

void emulator::processOperations(memopsT& memops)
{
  for (auto it = memops.begin(); it != memops.end(); it++) {
    if (it->type == READ_OP) {
      processRead(it->address);
    } else {
      processWrite(it->address);
    }
  }
}

void emulator::logStats()
{
  std::cout << "Page faults: " << stats.numPageFaults << "\n";
  std::cout << "Page writebacks: " << stats.numPageWrites << "\n";
}

}
