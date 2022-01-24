//===----------------------------------------------------------===//
// Utils module
//
// File purpose: global macro definitions
//===----------------------------------------------------------===//

#ifndef DEFS_H
#define DEFS_H

// Compilation flags
#define BOOST_ALL_DYN_LINK

// Global types

// Debugging control macros
// #define PRINT_EXECUTION_TIME

// Global variables
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#define LOG_LEVEL boost::log::trivial::error

#endif // #ifndef DEFS_H
