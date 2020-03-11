#ifndef __HERO_H__
#define __HERO_H__
#include "animate.h"
#include <string>
#include <vector>

class Hero: public Animate {
	
	std::vector<std::string> learnedItems;
	
	
	float goldMultiplier;
	float scoreMultiplier;
	std::string race;

	bool onStairs;
	std::string action;
	virtual void Die(Animate*);
	void checkSurroundings();
	bool itemIsLearned(Entity*);
	void learnItem(Entity*);
	
	public:
	Hero();
	Hero(int, int, int, bool, bool, bool, bool, int, std::string, bool, char, bool, bool, float, float, bool, std::string);
	Hero(const Hero&);
	~Hero();
	virtual void takeTurn(int);
	std::string getRace();
	int getGold();
	int getScore();
	virtual void Move(std::string direction);
	virtual void Attack(std::string);
	virtual void Consume(std::string);
	virtual int Defend(Animate*);
	bool isOnStairs();
	void getOffStairs();
	std::string getAction();
};


#endif
