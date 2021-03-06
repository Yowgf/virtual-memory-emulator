//===----------------------------------------------------------===//
// Interface module
//
// File purpose: init class header
//
// Description: this class validates user argument and gets it ready
// to be run on the target algorithm.
//===----------------------------------------------------------===//

#ifndef INIT_H
#define INIT_H

#include "Alg/emulator.hpp"
#include "Utils/time.hpp"

#include <string>
#include <vector>

namespace Interface {

// User input we expect (command line)
typedef struct {
  std::string chosenEmulatorStr;
  std::string filePath;
  unsigned pageSize;
  unsigned memorySize;
  
  Alg::emulator* chosenEmulator;
} inputT;

class init {
  
public:
  init(int argc, char** argv);
  ~init();

private:
  // Constraints
  static constexpr int minArgcAllowed = 5;
  static constexpr int maxArgcAllowed = 6;
  static constexpr unsigned maxFileNameLen = 0x100;
  const std::vector<std::string> allowedEmulators{"lru", "fifo", "newalg"};

  inputT userInput;

  bool isTestMode;

  void destroy();

  void initLogger();

  bool validateArguments(int argc, char** argv) const noexcept;
  inputT processEntries(int argc, char** argv);
  Alg::emulator* chooseAlg
    (std::string emulatorStr,
     unsigned pageSize,
     unsigned memorySize,
     std::string filePath);
  clockT timeRunAlg(Alg::emulator* alg);

  void printHeader();
  void printFooter(clockT executionTime);
  void printExecTime(clockT executionTime);
};

}

#endif
