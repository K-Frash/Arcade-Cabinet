#ifndef __WEREWOLF_H__
#define __WEREWOLF_H__
#include "enemy.h"

class Werewolf: public Enemy {
 public:
  Werewolf(): Enemy('W', 120, 30, 5) {}
};

#endif
