
#include "Memory/vtable.hpp"

struct compare_dummy {
  bool operator()(const Memory::pageT& p1, const Memory::pageT& p2) const {
    return p1.id > p2.id;
  }
};

using dummyvt = Memory::vtable<compare_dummy>;

struct vtablef {
  vtablef() : vtable(2, 4)
  {}

  dummyvt vtable;
};

BOOST_FIXTURE_TEST_CASE(vtable_read_empty_fault, vtablef)
{
  BOOST_TEST(vtable.read(0x10000000).wasPageFound == false);
  BOOST_TEST(vtable.read(0x20000000).wasPageFound == false);
  BOOST_TEST(vtable.read(0x30000000).wasPageFound == false);
}

BOOST_FIXTURE_TEST_CASE(vtable_read_1page_no_fault, vtablef)
{
  vtable.insertNewPage(0x10000000);
  BOOST_TEST(vtable.read(0x10000020).wasPageFound == true);
}

BOOST_FIXTURE_TEST_CASE(vtable_write_empty_fault, vtablef)
{
  BOOST_TEST(vtable.write(0x10000000).wasPageFound == false);
  BOOST_TEST(vtable.write(0x20000000).wasPageFound == false);
  BOOST_TEST(vtable.write(0x30000000).wasPageFound == false);
}

BOOST_FIXTURE_TEST_CASE(vtable_write_1page_no_fault, vtablef)
{
  vtable.insertNewPage(0x10000000);
  BOOST_TEST(vtable.write(0x10000020).wasPageFound == true);
}

BOOST_FIXTURE_TEST_CASE(vtable_empty_not_full, vtablef)
{
  BOOST_TEST(vtable.full() == false);
}

BOOST_FIXTURE_TEST_CASE(vtable_full_is_full, vtablef)
{
  vtable.insertNewPage(0x10000000);
  vtable.insertNewPage(0x20000000);
  BOOST_TEST(vtable.full() == true);
}

BOOST_FIXTURE_TEST_CASE(vtable_replaceTopPage_empty, vtablef)
{
  BOOST_TEST(vtable.replaceTopPage(0x10000000) == false);
}

BOOST_FIXTURE_TEST_CASE(vtable_replaceTopPage_cleanPage, vtablef)
{
  vtable.insertNewPage(0x10000000);
  vtable.insertNewPage(0x20000000);
  BOOST_TEST(vtable.replaceTopPage(0x20000000) == false);
}

BOOST_FIXTURE_TEST_CASE(vtable_replaceTopPage_dirtyPage, vtablef)
{
  vtable.insertNewPage(0x10000000);
  vtable.insertNewPage(0x20000000);
  vtable.write(0x10000000);
  // 0x10000000 should be the top page by the rule we defined in compare_dummy
  BOOST_TEST(vtable.replaceTopPage(0x20000000) == true);
}
