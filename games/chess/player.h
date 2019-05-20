#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <utility>
#include "posn.h"

class Player {
  bool failed;
 protected:
  void setFail() { failed = true; }
  void clearFail() { failed = false; }

 public:
  Player(): failed(false) {}
  
  operator bool() { return !failed; }
  bool fail() const { return failed; }
  virtual std::pair<Posn,Posn> getMove()=0;
  virtual char promote() = 0;
  virtual ~Player();
};

#endif
