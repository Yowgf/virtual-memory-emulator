//===----------------------------------------------------------===//
// Interface module
//
// File purpose: init class implementation. See class header for
// more detail.
//===----------------------------------------------------------===//

#include "Alg/lru.hpp"
#include "Alg/fifo.hpp"
#include "Alg/newalg.hpp"
#include "Interface/init.hpp"
#include "Utils/file.hpp"
#include "Utils/error.hpp"

#include <bits/stdc++.h>
#include <iomanip>
#include <iostream>
#include <string>

#define INRANGE(n, a, b) (a <= n && n <= b)

using namespace Utils;

namespace Interface {
  
init::init(int argc, char** argv)
{
  const bool areValid = validateArguments(argc, argv);
  if (!areValid) {
    throw std::invalid_argument {"Invalid program arguments"\
                                   "\nUsage: <program> <emulator>"\
                                   " <input-file> <page-size> <memory-size>"};
  }

  Alg::emulator* chosenAlg = processEntries(argc, argv);

  try {
    timeRunAlg(*chosenAlg);
  }
  catch(std::exception&) {
    destroy();
    throw;
  }
}

init::~init()
{
  destroy();
}

void init::destroy()
{}

void init::timeRunAlg(Alg::emulator& alg)
{
  auto before = std::chrono::high_resolution_clock::now();
  alg.run();
  auto executionTime = std::chrono::high_resolution_clock::now() - before;

  printOutput(alg, executionTime);
}

bool init::validateArguments(int argc, char** argv) const noexcept
{
  if (!INRANGE(argc, minArgcAllowed, maxArgcAllowed)) {
    return false;
  }

  const char* fileName = argv[2];
  if (!file::exists(fileName)) {
    return false;
  }

  if (std::char_traits<char>::length(argv[2]) > maxFileNameLen) {
    return false;
  }

  const auto emulator = std::string(argv[1]);
  if (std::find(std::begin(allowedEmulators),
		std::end(allowedEmulators),
		emulator)
      == std::end(allowedEmulators)) {
    return false;
  }
  
  return true;
}

Alg::emulator* init::processEntries(int argc, char** argv)
{
  auto emulatorStr = std::string(argv[1]);
  auto filePath = std::string(argv[2]);
  int pageSize = 0;
  int memorySize = 0;

  std::stringstream ss;
  ss << argv[3]; ss >> pageSize;
  ss << argv[4]; ss >> memorySize;

  auto emulator = chooseAlg(emulatorStr);
  emulator->configure(pageSize, memorySize, filePath);

  return emulator;
}

Alg::emulator* init::chooseAlg(std::string emulatorStr)
{
  if (emulatorStr == "lru") {
    return new Alg::lru;
  } else if (emulatorStr == "fifo") {
    return new Alg::fifo;
  } else if (emulatorStr == "newalg") {
    return new Alg::newalg;
  } else {
    throw std::runtime_error(std::string("Invalid emulator ") + emulatorStr);
  }
}

void init::printOutput(Alg::emulator& alg, clockT executionTime)
{
  std::cout << "(TODO) example output of emulator" << std::endl;
}

}
