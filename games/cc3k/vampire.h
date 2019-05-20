#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__
#include "enemy.h"

class Vampire: public Enemy {
 public:
  Vampire(): Enemy('V', 50, 25, 25) {}
};

#endif
