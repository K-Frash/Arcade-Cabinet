#ifndef __DAMAGETARGET_H_
#define __DAMAGETARGET_H_

#include "../ability.h"

class DamageOnTarget: public Ability{
protected:
	int cost = 1;
	AType type = AType::Trigger;
public:
	void activateOnMinion(std::unique_ptr<Minion> &minion, Player &player, Game &game);
};

#endif // __DAMAGETARGET_H_
