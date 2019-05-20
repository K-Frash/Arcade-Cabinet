#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "character.h"

class Player: public Character {
 public:
  Player(int hp, int atk, int def): Character('@', hp, atk, def) {}
};

#endif
