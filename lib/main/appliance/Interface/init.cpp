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
#include "Utils/defs.hpp"
#include "Utils/file.hpp"

#include <iomanip>
#include <iostream>
#include <string>

#define INRANGE(n, a, b) (a <= n && n <= b)

using namespace Utils;
namespace logger = boost::log;

namespace Interface {
  
init::init(int argc, char** argv) : isTestMode(false)
{
  const bool areValid = validateArguments(argc, argv);
  if (!areValid) {
    throw std::invalid_argument {"Invalid program arguments"\
                                   "\nUsage: <program> <emulator>"\
                                   " <input-file> <page-size> <memory-size>"\
				   " [<test-mode>]"};
  }

  try {
    initLogger();
    userInput = processEntries(argc, argv);
    if (!isTestMode) {
      printHeader();
    }
    auto executionTime = timeRunAlg(this->userInput.chosenEmulator);
    printFooter(executionTime);
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

#pragma GCC diagnostic ignored "-Wdelete-non-virtual-dtor"
void init::destroy()
{
  auto emulatorStr = userInput.chosenEmulatorStr;
  if (emulatorStr == "lru") {
    delete reinterpret_cast<Alg::lru*>(this->userInput.chosenEmulator);
  } else if (emulatorStr == "fifo") {
    delete reinterpret_cast<Alg::fifo*>(this->userInput.chosenEmulator);
  } else if (emulatorStr == "newalg") {
    delete reinterpret_cast<Alg::newalg*>(this->userInput.chosenEmulator);
  }
}

void init::initLogger()
{
    logger::core::get()->set_filter
    (
        logger::trivial::severity >= LOG_LEVEL
    );
}

clockT init::timeRunAlg(Alg::emulator* alg)
{
  auto before = std::chrono::high_resolution_clock::now();
  alg->run();
  return std::chrono::high_resolution_clock::now() - before;
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

inputT init::processEntries(int argc, char** argv)
{
  std::string emulatorStr{argv[1]};
  std::string filePath{argv[2]};
  unsigned pageSize = 0;
  unsigned memorySize = 0;

  std::stringstream ss;
  ss << argv[3]; ss >> pageSize; ss.clear();
  ss << argv[4]; ss >> memorySize; ss.clear();

  if (argc == maxArgcAllowed && std::string(argv[5]) == "test") {
    isTestMode = true;
  }
  
  auto* emulator = chooseAlg(emulatorStr, pageSize, memorySize, filePath);

  inputT input{emulatorStr, filePath, pageSize, memorySize, emulator};

  return input;
}

Alg::emulator* init::chooseAlg
  (std::string emulatorStr,
   unsigned pageSize,
   unsigned memorySize,
   std::string filePath)
{
  if (emulatorStr == "lru") {
    return new Alg::lru(pageSize, memorySize, filePath);
  } else if (emulatorStr == "fifo") {
    return new Alg::fifo(pageSize, memorySize, filePath);
  } else if (emulatorStr == "newalg") {
    return new Alg::newalg(pageSize, memorySize, filePath);
  } else {
    throw std::runtime_error(std::string("Invalid emulator ") + emulatorStr);
  }
}

void init::printHeader()
{
  std::cout << "Running the emulator...\n";
  std::cout << "Input file: " << userInput.filePath << "\n";
  std::cout << "Memory size: " << userInput.memorySize << "\n";
  std::cout << "Page size: " << userInput.pageSize << "\n";
  std::cout << "Page replacement strategy: " << userInput.chosenEmulatorStr << "\n";
}

void init::printFooter(clockT executionTime)
{
  userInput.chosenEmulator->logStats(isTestMode);
#ifdef PRINT_EXECUTION_TIME
  printExecTime(executionTime);
#endif
}

void init::printExecTime(clockT executionTime)
{
  double clkCount = executionTime.count();
  if (isTestMode) {
    std::cout << std::setprecision(6) << std::fixed << clkCount << '\n';
  } else {
    std::cout << "Execution time (seconds): " << std::setprecision(6) << std::fixed << clkCount << "\n";
  }
}

}
