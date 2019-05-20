#ifndef __HUMAN_H__
#define __HUMAN_H__
#include "player.h"

class Human: public Player {
 public:
  Human(): Player(140, 20, 20) {}
};

#endif
