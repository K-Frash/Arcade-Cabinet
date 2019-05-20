#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include "entity.h"

class Character: public Entity {
  int hp, atk, def;
 public:
  Character(char rep, int hp, int atk, int def): Entity(rep), hp(hp), atk(atk), def(def) {}
  virtual ~Character() = 0;
};

#endif
