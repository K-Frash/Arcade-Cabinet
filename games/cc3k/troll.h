#ifndef __TROLL_H__
#define __TROLL_H__
#include "enemy.h"

class Troll: public Enemy {
 public:
  Troll(): Enemy('T', 120, 25, 15) {}
};

#endif
