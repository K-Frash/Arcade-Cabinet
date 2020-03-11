#ifndef __STANDSTILL_H_
#define __STANDSTILL_H_

#include "../ritual.h"

class StandStill: public Ritual {
public:
	StandStill(const CardBase &base, int charges, int activationCost);
	StandStill(StandStill &&other); 
	virtual std::unique_ptr<Card> copy() const override;
	virtual void onMinionETB(Minion &minion, Player &player, Game &game) override;
};

#endif // __STANDSTILL_H_
