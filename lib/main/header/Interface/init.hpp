//===----------------------------------------------------------===//
// Interface module
//
// File purpose: init class header
//
// Description: this class validates user argument and gets it ready
// to be run on the target algorithm
//===----------------------------------------------------------===//

#ifndef INIT_H
#define INIT_H

namespace Interface {

class init {
  
public:
  init(int argc, char** argv);
  ~init();

private:
  void destroy();
};

}

#endif
