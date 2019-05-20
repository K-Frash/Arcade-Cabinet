#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "character.h"

class Enemy: public Character {
 public:
  Enemy(char rep, int hp, int atk, int def): Character(rep, hp, atk, def) {}
  virtual bool hostile() const { return true; }
};

#endif
