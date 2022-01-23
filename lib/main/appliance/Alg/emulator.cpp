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

emulator::emulator() : pageSize(0), memorySize(0), stats(statsT{0, 0})
{}

void emulator::configure(std::string filePath)
{
  decodeFile(filePath);
}

void emulator::decodeFile(std::string filePath)
{
  auto file = std::ifstream{filePath, std::ifstream::in};
  while (file.good()) {
    auto op = memopT{};
    file >> std::hex >> op.address >> op.type;
    if (!file.eof()) {
      memops.push_back(op);
    }
  }
  // Something went wrong while reading file
  if (!file.eof()) {
    char buffer[128];
    sprintf(buffer, "Error while decoding file for emulator. "	\
	    "State of the stream: %d %d %d %d",
	    file.good(), file.eof(), file.fail(), file.bad());
    throw std::runtime_error(buffer);
  }
  BOOST_LOG_TRIVIAL(info) << "Read " << memops.size() << " memory operations "
			  << "from input file";
}

void emulator::logStats(bool isTestMode)
{
  if (isTestMode) {
    std::cout << stats.numPageFaults << ' ' << stats.numPageWrites << ' ';
  } else {
    std::cout << "Page faults: " << stats.numPageFaults << "\n";
    std::cout << "Page writebacks: " << stats.numPageWrites << "\n";
  }
}

}
