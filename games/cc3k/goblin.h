#ifndef __GOBLIN_H__
#define __GOBLIN_H__
#include "enemy.h"

class Goblin: public Enemy {
 public:
  Goblin(): Enemy('N', 70, 5, 10) {}
};

#endif
