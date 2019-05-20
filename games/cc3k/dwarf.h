#ifndef __DWARF_H__
#define __DWARF_H__
#include "player.h"

class Dwarf: public Player {
 public:
  Dwarf(): Player(100, 20, 30) {}
};

#endif
