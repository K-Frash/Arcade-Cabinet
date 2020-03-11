#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "animate.h"

class Enemy: public Animate {
	public:
	Enemy();
	Enemy(int, int, int, bool, bool, bool, bool, int, std::string, bool, char, bool, bool, bool, int);
	Enemy(const Enemy&);
	~Enemy();
	
	virtual void takeTurn(int);
	virtual bool getHostility();
	
};


#endif