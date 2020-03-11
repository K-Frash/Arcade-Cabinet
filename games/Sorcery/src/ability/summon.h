#ifndef __SUMMON_H_
#define __SUMMON_H_

#include "../ability.h"
#include <string>

class Summon: public Ability{
protected:
	int cost;
	AType type;
	int amount; 
	const std::string &minion;
public:
	Summon(int cost, int amount, const std::string &minion);
	void activateOnGame(Game &game);
};


#endif // __SUMMON_H_
