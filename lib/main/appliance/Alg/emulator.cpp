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

void emulator::configure(int pageSize, int memorySize, std::string filePath)
{
  this->pageSize = pageSize;
  this->memorySize = memorySize;
  decodeFile(filePath);
}

void emulator::decodeFile(std::string filePath)
{
  auto file = std::ifstream{filePath, std::ifstream::in};
  int i = 0;
  while (file.good()) {
    auto op = memop{};
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

}
