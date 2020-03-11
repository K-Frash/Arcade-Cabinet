#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "hero.h"

class Player {
		Hero* hero;
		public:
		Player(Hero*);
		~Player();
		
		void move(std::string direction);
		void attack();
		void consume();
		Hero* getHero();
		
		bool isDead();
		
		int getScore();
		
};

#endif