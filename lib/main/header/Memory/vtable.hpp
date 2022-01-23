//===----------------------------------------------------------===//
// Memory module
//
// File purpose: ~vtable~ class declaration.
//===----------------------------------------------------------===//

#ifndef MEMORY_VTABLE_H
#define MEMORY_VTABLE_H

#include "Utils/defs.hpp"
#include "Utils/time.hpp"

#include <boost/heap/fibonacci_heap.hpp>

#include <limits>
#include <vector>

namespace Memory {

constexpr unsigned KB = 1024;

typedef struct {
  unsigned id;
  // TODO: make the metrics a union, once I have a better notion of how that
  // should work.
  long int lastUsedAt;
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
    pagesz(pageSize), memsz(memorySize)
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
    BOOST_LOG_TRIVIAL(debug) << "(vtable) performing memory read. (address="
			     << address << ")";
    auto pageId = pageidFromAddr(address);
    return vtableOpRespT{.wasPageFound = status[pageId].active};
  }

  vtableOpRespT write(unsigned address)
  {
    BOOST_LOG_TRIVIAL(debug) << "(vtable) performing memory write. (address="
			     << address << ")";
    auto pageId = pageidFromAddr(address);
    status[pageId].dirty = true;
    return vtableOpRespT{.wasPageFound = status[pageId].active};
  }

  bool full()
  {
    return pages.size() * pagesz * KB >= memsz * KB;
  }

  bool replaceTopPage(unsigned address)
  {
    bool wasDirty = false;
    if (!pages.empty()) {
      auto oldPageId = pages.top().id;
      wasDirty = removePage(oldPageId);
    }
    insertNewPage(pageidFromAddr(address));
    return wasDirty;
  }

  void insertNewPage(unsigned address) {
    using namespace std::chrono;
    auto pageId = pageidFromAddr(address);
    auto currentTime = time_point_cast<nanoseconds>(high_resolution_clock::now()).time_since_epoch().count();
    BOOST_LOG_TRIVIAL(debug) << "(vtable) inserting new page (address="
			     << address << " pageid=" << pageId
			     << " currentTime=" << currentTime << ")";
    pages.push(pageT{.id = pageId, .lastUsedAt = currentTime});
    status[pageId].active = true;
    status[pageId].dirty = false;
  }

private:
  unsigned pagesz;
  unsigned memsz;

  unsigned lowestBits;

  pagesT pages;
  std::vector<pageStatusT> status;

  unsigned findLowestBits(unsigned pageSize)
  {
    pageSize *= KB;
    unsigned lowestBits = 0;
    while (pageSize > 1) {
      lowestBits++;
      pageSize >>= 1;
    }
    return lowestBits;
  }

  bool removePage(unsigned pageId)
  {
    bool isDirty = status[pageId].dirty;
    status[pageId].active = false;
    status[pageId].dirty = false;
    return isDirty;
  }

  unsigned pageidFromAddr(unsigned address)
  {
    return address >> lowestBits;
  }
};

}

#endif
