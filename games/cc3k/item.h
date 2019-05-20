#ifndef __ITEM_H__
#define __ITEM_H__
#include "entity.h"

class Item: public Entity {
 public:
  Item(char rep, int hp, int atk, int def): Entity(rep) {}
  virtual ~Item() = 0;
};

#endif
