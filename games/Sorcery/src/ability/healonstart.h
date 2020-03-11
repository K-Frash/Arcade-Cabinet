#ifndef __HEALONSTART_H_
#define __HEALONSTART_H_

#include "../ability.h"

class HealOnStart: public Ability{
	protected:
	int cost = 0;
	AType type = AType::Trigger;
	public:
	void onTurnStart(Game &game) override;
};

#endif // __HEALONSTART_H_
