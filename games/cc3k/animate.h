#ifndef __ANIMATE_H__
#define __ANIMATE_H__
#include <string>
#include "entity.h"
#include "animate.h"
#include "tile.h"

class Animate: public Entity {
	
	bool negateHarmfulEffects;
	
	void takeGold(Entity*);
	virtual void Die(Animate* killer);
	virtual void setHostile();
	
	protected:
	int lastMovedTurn;
	
	void addBAtk(int);
	void addBDef(int);
	void addBHp(int);
	void pickupGold(Entity*);
	
	public:
		Animate();
		Animate(int, int, int, bool, bool, bool, bool, int, std::string, bool, char, bool, bool, bool, int);
		Animate(const Animate&);
		~Animate();
		
		virtual void Move(std::string);
		virtual void Attack(std::string);
		virtual void Consume(std::string);
		virtual int Defend(Animate*);
		virtual void takeTurn(int)=0;
};


#endif