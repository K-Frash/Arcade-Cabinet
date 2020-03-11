#ifndef __NEUTRAL_H__
#define __NEUTRAL_H__
#include "enemy.h" 
#include "inanimate.h"

class Neutral: public Enemy {
	Inanimate* treasure;
	bool* globalHostility;
	bool masterCopy;
	
	public:
	
	Neutral();
	Neutral(int, int, int, bool, bool, bool, bool, int, std::string, bool, char, bool, bool, bool, int, Inanimate*);
	Neutral(const Neutral&);
	~Neutral();

	virtual bool getHostility();
	virtual void setHostile();
	void freeSharedResources();
	virtual void Die(Animate* killer);
	
};


#endif