#ifndef __MERCHANT_H__
#define __MERCHANT_H__
#include "enemy.h"

class Merchant: public Enemy {
  static bool isHostile;
 public:
  Merchant(): Enemy('M', 30, 70, 5) {}
  bool hostile() { return isHostile; }
};

#endif
