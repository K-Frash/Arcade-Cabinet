#ifndef __HUMAN_H__
#define __HUMAN_H__
#include <iostream>
#include "posn.h"
#include "player.h"

class Human: public Player {
  std::istream &in;
 public:
  Human(std::istream &in=std::cin);
  virtual Move getMove();
  char promote();
  virtual ~Human();
};

#endif
