
#include "Memory/vtable.hpp"

struct compare_dummy {
  bool operator()(const Memory::pageT& n1, const Memory::pageT& n2) const {
    return true;
  }
};

using dummyvt = Memory::vtable<compare_dummy>;

BOOST_AUTO_TEST_CASE(vtable_read)
{
  unsigned pageSize = 2;
  unsigned memorySize = 4;

  dummyvt vtable{pageSize, memorySize};
}
