#ifndef __ELF_H__
#define __ELF_H__
#include "player.h"

class Elf: public Player {
 public:
  Elf(): Player(140, 30, 10) {}
};

#endif
