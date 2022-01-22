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
  const bool isProgArgsValid = validateArguments(argc, argv);
  if (!isProgArgsValid) {
    throw std::invalid_argument {"Invalid program arguments"\
                                   "\nUsage: <program> <algorithm>"\
                                   " <input-file> <page-size> <memory-size>"};
  }

  Alg::algorithm* chosenAlg = processEntries(argc, argv);

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

void init::timeRunAlg(Alg::algorithm& alg)
{
  auto before = std::chrono::high_resolution_clock::now();
  alg.run();
  auto clkVar = std::chrono::high_resolution_clock::now() - before;

  printOutput(alg, clkVar);
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

  const auto algorithm = std::string(argv[1]);
  if (std::find(std::begin(allowedAlgorithms),
		std::end(allowedAlgorithms),
		algorithm)
      == std::end(allowedAlgorithms)) {
    return false;
  }
  
  return true;
}

Alg::algorithm* init::processEntries(int argc, char** argv)
{
  auto algorithmStr = std::string(argv[1]);
  return chooseAlg(algorithmStr);
}

Alg::algorithm* init::chooseAlg(std::string algorithmStr)
{
  if (algorithmStr == "lru") {
    return new Alg::lru;
  } else if (algorithmStr == "fifo") {
    return new Alg::fifo;
  } else if (algorithmStr == "newalg") {
    return new Alg::newalg;
  } else {
    throw std::runtime_error(std::string("Invalid algorithm ") + algorithmStr);
  }
}

void init::printOutput(Alg::algorithm& alg, clockT executionTime)
{
  std::cout << "(TODO) example output of algorithm" << std::endl;
}

}
