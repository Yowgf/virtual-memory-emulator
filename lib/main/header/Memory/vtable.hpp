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
  // TODO: remove this field
  unsigned id;
  // TODO: make the metrics a union

  // Last time page was used (either a read or write) in nanoseconds
  long int lastUsedAt;
  // Time of creation of the page in nanoseconds
  long int createdAt;
  // Number of times page was used last time it was it memory. This needs to be
  // kept here and in the status vector. The reason is:
  //
  // - It needs to be here to order the heap
  // - It needs to be in the status vector so that we can quickly access it
  unsigned historyUses;
} pageT;

typedef struct {
  bool active;
  bool dirty;
  unsigned historyUses;
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
    status = std::vector<pageStatusT>
      {
        numPages,
	pageStatusT{.active=false, .dirty=false, .historyUses=0}
      };
  }

  vtableOpRespT read(unsigned address)
  {
    BOOST_LOG_TRIVIAL(debug) << "(vtable) performing memory read. (address="
			     << address << " pagesz=" << pagesz << ")";
    auto pageId = pageidFromAddr(address);
    status[pageId].historyUses++;
    return vtableOpRespT{.wasPageFound = status[pageId].active};
  }

  vtableOpRespT write(unsigned address)
  {
    BOOST_LOG_TRIVIAL(debug) << "(vtable) performing memory write. (address="
			     << address << " pagesz=" << pagesz << ")";
    auto pageId = pageidFromAddr(address);
    status[pageId].historyUses++;
    bool wasFound = status[pageId].active;
    if (wasFound) {
      status[pageId].dirty = true;
    }
    return vtableOpRespT{.wasPageFound = wasFound};
  }

  bool full()
  {
    return pages.size() * pagesz >= memsz;
  }

  void insertNewPage(unsigned address) {
    auto pageId = pageidFromAddr(address);
    auto currentTime = Utils::time::now_nanoseconds();
    BOOST_LOG_TRIVIAL(debug) << "(vtable) inserting new page (address="
			     << address << " pageid=" << pageId
			     << " currentTime=" << currentTime << ")";

    pageT newPage{.id = pageId};
    if (!status[pageId].active) {
      newPage.createdAt = currentTime;
      newPage.historyUses = status[pageId].historyUses;
      status[pageId].historyUses = 0;
    }
    newPage.lastUsedAt = currentTime;

    pages.push(newPage);
    status[pageId].active = true;
    status[pageId].dirty = false;
  }

  bool replaceTopPage(unsigned address)
  {
    bool wasDirty = false;
    if (!pages.empty()) {
      auto oldPageId = pages.top().id;
      pages.pop();
      wasDirty = removePage(oldPageId);
    }
    insertNewPage(pageidFromAddr(address));
    return wasDirty;
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

  unsigned pageidFromAddr(unsigned address)
  {
    return address >> lowestBits;
  }

  bool removePage(unsigned pageId)
  {
    BOOST_LOG_TRIVIAL(debug) << "(vtable) removing page (pageId="
			     << pageId << ")";
    bool isDirty = status[pageId].dirty;
    status[pageId].active = false;
    status[pageId].dirty = false;
    return isDirty;
  }
};

}

#endif
