#ifndef __DRAGON_H__
#define __DRAGON_H__
#include "enemy.h"

class Dragon: public Enemy {
 public:
  Dragon(): Enemy('D', 150, 20, 20) {}
};

#endif
