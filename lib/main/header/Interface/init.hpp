//===----------------------------------------------------------===//
// Interface module
//
// File purpose: init class header
//
// Description: this class validates user argument and gets it ready
// to be run on the target algorithm
//===----------------------------------------------------------===//

#ifndef INIT_H
#define INIT_H

#include "Alg/emulator.hpp"
#include "Utils/time.hpp"

#include <string>
#include <vector>

namespace Interface {

typedef std::chrono::duration<long int, std::ratio<1, 1000000000>> clockT;

class init {
  
public:
  init(int argc, char** argv);
  ~init();

private:
  // Constraints
  static constexpr int minArgcAllowed = 5;
  static constexpr int maxArgcAllowed = 5;
  static constexpr unsigned maxFileNameLen = 0x100;
  const std::vector<std::string> allowedEmulators{"lru", "fifo", "newalg"};

  void destroy();

  Alg::emulator* processEntries(int argc, char** argv);
  Alg::emulator* chooseAlg(std::string emulatorStr);
  bool validateArguments(int argc, char** argv) const noexcept;

  void timeRunAlg(Alg::emulator& alg);
  void printOutput(Alg::emulator& alg, clockT executionTime);
};

}

#endif
