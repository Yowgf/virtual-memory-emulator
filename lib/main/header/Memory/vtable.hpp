//===----------------------------------------------------------===//
// Memory module
//
// File purpose: ~vtable~ class declaration.
//===----------------------------------------------------------===//

#ifndef MEMORY_VTABLE_H
#define MEMORY_VTABLE_H

#include "Utils/defs.hpp"

#include <boost/heap/fibonacci_heap.hpp>

#include <limits>
#include <vector>

namespace Memory {

constexpr unsigned KB = 1024;

typedef struct {
  unsigned id;
  unsigned startAddr;
  // TODO: make the metrics a union, once I have a better notion of how that
  // should work.
  unsigned lastUsedAt;
} pageT;

typedef struct {
  bool active;
  bool dirty;
} pageStatusT;

typedef struct {
  bool wasPageFound;
} vtableOpRespT;

template<typename compare>
class vtable {

typedef boost::heap::fibonacci_heap<pageT, boost::heap::compare<compare>> pagesT;

public:
  vtable(unsigned pageSize, unsigned memorySize) :
    pagesz(pageSize*KB), memsz(memorySize*KB)
  {
    BOOST_LOG_TRIVIAL(info) << "(vtable) initializing vtable (pageSize="
			    << pageSize << " memorySize=" << memorySize << ")";
    if (pageSize == 0 || memorySize == 0) {
      throw std::invalid_argument{"invalid arguments to vtable constructor"};
    }
    lowestBits = findLowestBits(this->pagesz);
    unsigned numPages = std::numeric_limits<unsigned>::max() >> lowestBits;
    status = std::vector<pageStatusT>{numPages, pageStatusT{.active=false, .dirty=false}};
  }

  vtableOpRespT read(unsigned address)
  {
    BOOST_LOG_TRIVIAL(debug) << "(vtable) performing page read. (address=" << address << ")";
    auto pageId = pageidFromAddr(address);
    return vtableOpRespT{.wasPageFound = status[pageId].active};
  }

  vtableOpRespT write(unsigned address)
  {
    auto pageId = pageidFromAddr(address);
    status[pageId].dirty = true;
    return vtableOpRespT{.wasPageFound = status[pageId].active};
  }

  bool full()
  {
    return pages.size() * KB >= memsz;
  }

  bool replaceTopPage()
  {
    auto pageId = pages.top().id;
    auto& pageStatus = status[pageId];
    bool ret = pageStatus.dirty;

    pageStatus.dirty = false;
    pages.pop();
    pages.push({.id = pageId, .lastUsedAt = 0});

    return ret;
  }

  void insertNewPage(unsigned address) {
    auto pageId = pageidFromAddr(address);
    pages.push(pageT{.id = pageId, .lastUsedAt = 0});
    status[pageId] = pageStatusT{.active = true, .dirty = false};
  }

private:
  unsigned pagesz;
  unsigned memsz;

  unsigned lowestBits;

  pagesT pages;
  std::vector<pageStatusT> status;

  unsigned findLowestBits(unsigned pageSize)
  {
    unsigned lowestBits = 0;
    while (pageSize > 1) {
      lowestBits++;
      pageSize >>= 1;
    }
    return lowestBits;
  }

  unsigned pageidFromAddr(unsigned address)
  {
    return address >> lowestBits;
  }
};

}

#endif
