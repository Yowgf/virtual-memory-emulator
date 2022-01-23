#include "Utils/defs.hpp"

#define BOOST_TEST_MODULE All_Tests

#include <boost/test/included/unit_test.hpp>

namespace logger = boost::log;

struct Fixture {
  Fixture() {
    logger::core::get()->set_filter(
       logger::trivial::severity >= logger::trivial::debug
    );
  }
  ~Fixture() {}
};

BOOST_GLOBAL_FIXTURE(Fixture);

#include "Memory/vtable_test.cpp"
