//===----------------------------------------------------------===//
// Interface module
//
// File purpose: init class implementation. See class header for
// more detail.
//===----------------------------------------------------------===//

#include "Interface/init.hpp"

namespace Interface {
  
init::init(int argc, char** argv)
{}

init::~init()
{
  destroy();
}

void init::destroy()
{}
 
}
