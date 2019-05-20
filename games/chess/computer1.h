#ifndef __COMPUTER1_H__
#define __COMPUTER1_H__
#include <utility>
#include "posn.h"
#include "computer.h"

class Computer1: public Computer {
 public:
  Computer1(Board &b): Computer(b) {}
  std::pair<Posn,Posn> getMove();
  char promote();
};

#endif
