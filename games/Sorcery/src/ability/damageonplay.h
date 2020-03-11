#ifndef __DAMAGEONPLAY_H_
#define __DAMAGEONPLAY_H_

#include "../ability.h"

class DamageOnPlay: public Ability{
	protected:
	int cost = 0;
	AType type = AType::Trigger;
	public:
	void onMinionETB(Minion &minion, Player &player, Game &game) override;
};


#endif // __DAMAGEONPLAY_H_
