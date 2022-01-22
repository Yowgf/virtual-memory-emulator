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

#include "Alg/algorithm.hpp"
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
  static constexpr int minArgcAllowed = 5;
  static constexpr int maxArgcAllowed = 5;
  static constexpr unsigned maxFileNameLen = 0x100;
  const std::vector<std::string> allowedAlgorithms{"lru", "fifo", "newalg"};

  void destroy();

  Alg::algorithm* processEntries(int argc, char** argv);
  Alg::algorithm* chooseAlg(std::string algorithmStr);
  bool validateArguments(int argc, char** argv) const noexcept;

  void timeRunAlg(Alg::algorithm& alg);
  void printOutput(Alg::algorithm& alg, clockT executionTime);
};

}

#endif
