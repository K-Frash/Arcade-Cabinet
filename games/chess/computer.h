#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include <utility>
#include <vector>
#include "posn.h"
#include "player.h"
class Board;

class Computer: public Player {
  Board &b;
 protected:
  std::vector<std::pair<Posn,Posn> > myLegalMoves() const;
 public:
  Computer(Board &b): Player(), b(b) {}
  friend class Board;
};

#endif
