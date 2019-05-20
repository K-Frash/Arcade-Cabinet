#ifndef __PHOENIX_H__
#define __PHOENIX_H__
#include "enemy.h"

class Phoenix: public Enemy {
 public:
  Phoenix(): Enemy('X', 50, 35, 20) {}
};

#endif
