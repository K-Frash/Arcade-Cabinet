#ifndef __INANIMATE_H__
#define __INANIMATE_H__
#include "entity.h"
#include "animate.h"

class Inanimate: public Entity {
	public:
		Inanimate();
		Inanimate(int, int, int, bool, bool, bool, bool, int, std::string, bool, char, bool, bool, int);
		Inanimate(const Inanimate&);
		~Inanimate();
		virtual void takeTurn(int);
		void Consumed(Animate*);
		
		int getHp();
		int getAttack();
		int getDef();
	
};

#endif